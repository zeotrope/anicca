#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "char.h"
#include "memory.h"
#include "function.h"
#include "symbol.h"
#include "verb.h"
#include "lexer.h"
#include "parser.h"
#include "util.h"

VO print(A y) {
    C *cv; I yn=AN(y), *iv; D *dv; Z *zv; V *vv; A *bv;

    if (!y) { printf("NULL"); R; }

    switch (AT(y)) {
    case BOOL: { cv=BAV(y); DO(yn, printf("%d ", (I)cv[i])); break; }
    case NAME:
    case CHAR: { cv=CAV(y); DO(yn, printf("%c",  cv[i]));    break; }
    case INT:  { iv=IAV(y); DO(yn, printf("%d ", iv[i]));    break; }
    case FLT:  { dv=DAV(y); DO(yn, printf("%lf ",dv[i]));    break; }
    case CMPX: {
        zv=ZAV(y); DO(yn, printf("%lfj%lf ",ZR(zv[i]),ZI(zv[i]))); break;
    }
/* TODO?: fancy line drawings */
    case BOX: {
        bv = AAV(y);
        DO(AN(y), printf("(<");
           print(bv[i]);
           printf(")%s", (i+1 == AN(y))?"":",")
        );
        break;
    }
    case VERB: case ADV: case CONJ: {
        vv = VAV(y);
        printf("%c", vv->id);
        if (VF(vv)) { print(vv->f);
            if (VG(vv)) { print(vv->g);
                if (VH(vv)) { print(vv->h); };
            }
        };
        break;
    }
    case LPAR: { printf("LPAR"); break; }
    case RPAR: { printf("RPAR"); break; }
    case ASGN: { intf(y) ? printf("=:") : printf("=."); break; }
    case MARK: { break; }
    default:   { printf("HUH?"); break; }
    }
}

VO println(A y) { if (!(AT(y)&MARK)) { print(y); printf("\n"); } }

VO a_init(VO) {
    zero=sbool(0); one=sbool(1);
    ten=sint(10);  zone=scmpx(0,1);
    mark = gsa(MARK, 0, 0, NULL);
    lpar = gsa(LPAR, 0, 0, NULL);
    rpar = gsa(RPAR, 0, 0, NULL);
    symbinit();
}

I a_strtoi(I n, C *s, C **e) {  R (I)a_strtod(n,s,e); }

D a_strtod(I n, C *s, C**e) { I si=1; D v, p;
    if (*s==CUNDS) { si=-1; s++; }
    for (v=0;isdigit(*s);) { v=(10*v)+(*s++-'0'); }
    if (*s=='.') { s++; }
    for (p=1;isdigit(*s);) { v=(10*v)+(*s++-'0'); p*=10; }
    *e=s;
    R si*(v/p);
}

A eval(const C *str) {
    A w, y, z;
    w = gstr(strlen(str)+1, str);
    y = tokens(w);
    z = parse(y);
    /*freea(w); freea(y);*/
    a_free(w); a_free(y);
    R z;
}

VO a_repl(const C *s) {
    C *v, str[100]; A z;
    while (1) {
        printf("%s", s);
        v = fgets(str, sizeof(str), stdin);
        if (!v) break;

        v = strndup(str, strlen(str)-1); /* remove carriage return */
        println(z = eval(v));
        free(v);
    }
}
