#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "error.h"
#include "memory.h"
#include "char.h"
#include "table.h"
#include "convert.h"
#include "util.h"
#include "verb.h"
#include "lexer.h"
#include "noun.h"

#define NCOL 3
#define NROW 5

/* Noun Transition Table */
static ST noun[NROW][NCOL] = {
    /*SS*/ {{SM,ES},{SS,EO},{SX,EN}},
    /*SX*/ {{SM,EW},{SN,EW},{SA,EO}},
    /*SA*/ {{SM,EW},{SN,EW},{SA,EO}},
    /*SN*/ {{SM,ES},{SS,EO},{SX,EN}},
    /*SM*/ {{SS,ES},{SS,ES},{SS,ES}}
           /*  CX      CS      CA  */
};

/*
  noun_start
  input:  Length of noun, String of noun.
  output: Array of size 2n, in the form:
    [start index token 1, length token 1, start index token 2,
    length token 2, ..., start index token n, length token n].
*/
static A noun_index(I n, C *s) {
    C e, t, st = SS;
    I i, m = 1+n, j = 0, k = 0, *v;
    ST pr; A z = ga(INT, 1, m, NULL);
    v = IAV(z);

    DO(n, t = nountype[s[i]]; pr = noun[st][t];
       e = pr.effect; st = pr.new;

       switch (e) {
       case EO: break;
       case EN: j = i; break;
       case EW: v[k++] = j; v[k++] = i-j; break;
       case ES: goto end_noun; break;
       }
    );
  end_noun:
    ra(z, INT, k); AN(z) = k; R z;
}

NPARSE(base) { C *s;
    parse_pieul(n,sp,y); s=*sp;
    if (*s=='b') { parse_pieul(n,sp,y); }
    R 1;
}

NPARSE(pieul) {C *s=*sp, *e; I k; A p, q, x;
    parse_cmpx(n,sp,y); e=*sp;
    if (*e=='p')      { parse_cmpx(n,sp,y); }
    else if (*e=='x') {
        e++; p=*y; *y=sbool(0); k=n-(I)(e-s); *sp=e;
        ASSERT(parse_cmpx(k,sp,y),ERILLNUM);
        q=*y; *y=times(p,expntl(q));
    }
    R 1;
}

NPARSE(cmpx) { C *s=*sp, *e; I k; A p, q, x;
    parse_exp(n,sp,y); e=*sp;
    if (*e=='a') {
        if (*e=='d')      { parse_exp(n,sp,y); }
        else if (*e=='r') { parse_exp(n,sp,y); }
    }
    else if (*e=='j') {
        e++; p=*y; *y=sbool(0); k=n-(I)(e-s); *sp=e;
        ASSERT(parse_exp(n,sp,y),ERILLNUM);
        q=*y; *y=complex(p,q);
    }
    R 1;
}

NPARSE(exp) { C *s=*sp, *e; I k; A p, q, x;
    parse_rat(n,sp,y); e=*sp;
    if (*e=='e') {
        e++; p=*y; *y=sbool(0); k=n-(I)(e-s); *sp=e;
        ASSERT(parse_rat(k,sp,y),ERILLNUM);
        q=*y; *y=times(p,power(sint(10),q));
    }
    R 1;
}

NPARSE(rat) { C *s=*sp;
    parse_num(n,sp,y);
    if (*s=='r') { parse_num(n,sp,y); }
    R 1;
}

NPARSE(num) {
    C c=**sp, *s=*sp, *d=memchr(s,'.',n), *e;
    I si=1, iv; D dv; A w = *y;
    if (c==CUNDS) { si=-1; s++; }
    if (n==1&&(c==CZERO||c==CONE)) { *BAV(w)=c-CZERO; e=s+1; }
    else if (d) { w=conv(FLT,w); dv=a_strtod(n,s,&e); *DAV(w)=si*dv; }
    else        { w=conv(INT,w); iv=a_strtoi(n,s,&e); *IAV(w)=si*iv; }
    *y=w; *sp=e; R 1;
}

A parse_noun(I n, C *s) {
    B *bv; C *av, *zv, *ws; D *dv;
    A y=noun_index(n+1,s), nouns, z, atm, *nv;
    I m=AN(y)/2, t=0, ak, at, j, wi, wl, zk, *indx=IAV(y), *iv;
    nouns = ga(BOX, 1, m, NULL); nv = AAV(nouns);
    DO(m, j=i+i; wi=indx[j]; wl=indx[j+1]; ws=&s[wi];
       atm = nv[i] = sbool(0);
       ASSERT(parse_pieul(wl,&ws,&atm),ERILLNUM);
       t=MAX(at=AT(atm),t); nv[i]=atm;
    );

    if (m==1) { z = ca(atm); }
    else {
        z = ga(t, 1, m, NULL); zk = ts(t); zv = CAV(z)-zk;
        DO(m, atm=nv[i]; at=AT(atm); av=CAV(atm);
           if (at==t) { memcpy(zv+=zk, av, zk); }
           else { aconv(CNVCASE(at,t), 1, zv+=zk, av); }
        );
    }
    R z;
}
