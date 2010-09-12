#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "convert.h"
#include "util.h"
#include "verb-scalar.h"
#include "primitive.h"
#include "lexer.h"
#include "noun.h"

#define NCOL 3
#define NROW 5

/* Noun Transition Table */
static ST noundfa[NROW][NCOL] = {
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
A noun_index(I n, C *s) {
    C e, t, st=SS;
    I i, m=1+n, j=0, k=0, *v;
    ST pr; A z=ga(INT,1,m,NULL);
    v=IAV(z);

    DO(n, t=ntype(s[i]); pr=noundfa[st][t];
       e=pr.effect; st=pr.new;

       switch (e) {
       case EO:                       break;
       case EN: j=i;                  break;
       case EW: v[k++]=j; v[k++]=i-j; break;
       case ES: goto end_noun;        break;
       }
    );
  end_noun:
    z=ra(z,INT,k); R z;
}

NPARSE(base);
NPARSE(pieul);
NPARSE(cmpx);
NPARSE(exp);
NPARSE(rat);
NPARSE(num);

NPARSE(base) { NPROLOG(pieul);
    if (*e=='b') { ; }
    R 1;
}

NPARSE(pieul) { NPROLOG(cmpx);
    if (*e=='p')      { ; }
    else if (*e=='x') { NBODY(cmpx,times(p,expntl(q))); }
    R 1;
}

NPARSE(cmpx) { NPROLOG(exp);
    if (*e=='a') {
        if (*e=='d')      { NBODY(exp,complex(p,q)); }
        else if (*e=='r') { NBODY(exp,complex(p,q));  }
    }
    else if (*e=='j') { NBODY(exp,complex(p,q)); }
    R 1;
}

NPARSE(exp) { NPROLOG(rat);
    if (*e=='e') { NBODY(rat,times(p,power(ten,q))); }
    R 1;
}

NPARSE(rat) { NPROLOG(num);
    if (*e=='r') { ; }
    R 1;
}

NPARSE(num) { C c=**sp, *s=*sp, *d=memchr(s,'.',n), *e; A w = *y;
    if (n==1&&(c==CZERO||c==CONE)) { *BAV(w)=c-CZERO; e=s+1; }
    else if (d) { w=conv(FLT,w); *DAV(w)=a_strtod(n,s,&e); }
    else        { w=conv(INT,w); *IAV(w)=a_strtoi(n,s,&e); }
    *y=w; *sp=e; R 1;
}

A parse_noun(I n, C *s) {
    B *bv; C *av, *zv, *ws; D *dv;
    A y=noun_index(n+1,s), nouns, z, atm, *nv;
    I m=AN(y)/2, t=0, ak, at, j, wi, wl, zk, *indx=IAV(y), *iv;
    nouns=ga(BOX,1,m,NULL); nv=AAV(nouns);
    DO(m, j=i+i; wi=indx[j]; wl=indx[j+1]; ws=&s[wi];
       atm=sbool(0);
       ASSERT(parse_pieul(wl,&ws,&atm),ERILLNUM);
       t=MAX(at=AT(atm),t); nv[i]=atm;
    );

    if (m==1) { z = ca(atm); }
    else {
        z=ga(t,1,m,NULL); zk=ts(t); zv=CAV(z)-zk;
        DO(m, atm=nv[i]; at=AT(atm); av=CAV(atm);
           if (at==t) { MC(zv+=zk,av,zk); }
           else { aconv(CNVCASE(at,t), 1, zv+=zk, av); }
        );
    }
    R z;
}
