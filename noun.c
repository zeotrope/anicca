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
/*#include "atom.h"*/
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

    DO(n,
       t = nountype[s[i]];
       pr = noun[st][t];
       e = pr.effect;
       st = pr.new;

       switch (e) {
       case EO: break;
       case EN: j = i; break;
       case EW: v[k++] = j; v[k++] = i-j; break;
       case ES: goto end_noun; break;
       }
    );
  end_noun:
    ra(z, INT, k);
    AN(z) = k;
    R z;
}

NPARSE(base) {
    parse_pieul(n,s,y);
    if (*s=='b') { parse_pieul(n,s,y); }
    R 1;
}

NPARSE(pieul) {
    parse_cmpx(n,s,y);
    if (*s=='p')      { parse_cmpx(n,s,y); }
    else if (*s=='x') { parse_cmpx(n,s,y); }
    R 1;
}

NPARSE(cmpx) {
    parse_exp(n,s,y);
    if (*s=='a') { s++;
        if (*s=='d')      { parse_exp(n,s,y); }
        else if (*s=='r') { parse_exp(n,s,y); }
    }
    else if (*s=='j') { parse_exp(n,s,y); }
    R 1;
}

NPARSE(exp) {
    parse_rat(n,s,y);
    if (*s=='e') {
        ASSERT(parse_rat(n,s++,y),ERILLNUM);
    }
    R 1;
}

NPARSE(rat) {
    parse_num(n,s,y);
    if (*s=='r') { parse_num(n,s,y); }
    R 1;
}

NPARSE(num) {
    C c = *s, *d=memchr(s,'.',n), *e;
    I si = (*s==CUNDS) ? 1 : 0, iv; D dv; A w = *y;
    if (n==1&&(c==CZERO||c==CONE)) { *BAV(w)=c-CZERO; e=s+1; }
    else if (d) { w=conv(FLT,w); dv=strtod(s,&e);    *DAV(w)=si ? -(dv) : dv; }
    else        { w=conv(INT,w); iv=strtol(s,&e,10); *IAV(w)=si ? -(iv) : iv; }
    *y=w; s=e; R 1;
}

A parse_noun(I n, C *s) {
    B *bv; C *av, *zv, *ws; D *dv;
    A y=noun_index(n+1,s), nouns, z, atm, *nv;
    I m=AN(y)/2, t=0, ak, at, j, wi, wl, zk, *indx=IAV(y), *iv;
    nouns = ga(BOX, 1, m, NULL); nv = AAV(nouns);
    DO(m, j=i+i; wi=indx[j]; wl=indx[j+1]; ws=&s[wi];
       atm = nv[i] = ga(BOOL, 0, 1, NULL);
       ASSERT(parse_num(wl,ws,&atm),ERILLNUM);
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
