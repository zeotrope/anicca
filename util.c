#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "memory.h"
#include "function.h"
#include "verb.h"
#include "lexer.h"
#include "parser.h"
#include "util.h"

VO print(A y) {
    C *cv; I yn=AN(y), *iv; D *dv; Z *zv; V *vv; A *bv;

    if (!y) { printf("NULL"); R; }

    switch (AT(y)) {
    case BOOL: { cv=BAV(y); DO(yn, printf("%d ", (I)cv[i])); break; }
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
    case MARK: { printf("MARK"); break; }
    case LPAR: { printf("LPAR"); break; }
    case RPAR: { printf("RPAR"); break; }
    default:   { printf("HUH?"); break; }
    }
}

VO println(A y) {
    print(y);
    printf("\n");
}

VO a_init(VO) {
    zero=sbool(0); one=sbool(1); zone=scmpx(0,1);
    mark = ga(MARK, 0, 0, NULL);
    lpar = ga(LPAR, 0, 0, NULL);
    rpar = ga(RPAR, 0, 0, NULL);
}

I a_strtoi(I n, C *s, C **e) { I v=0, i;
    for (i=0;isdigit(*s)&&(i<n);i++) { v=(10*v)+(*s++-'0'); }
    *e=s; R v;
}

D a_strtod(I n, C *s, C**e) {
    C *d=memchr(s,'.',n); I k=d-s, m=n-(k+1); D p=1, a, b, v;
    a=(D)a_strtoi(k,s,e); s=*e;
    if (*s=='.') { s++; }
    b=(D)a_strtoi(m,s,e);
    DO(m, p*=10); v = (a + b/(D)p); R v;
}

A eval(const C *str) {
    A w, y, z;
    w = gstr(strlen(str)+1, str);
    y = tokens(w);
    z = parse(y);
    a_free(w); a_free(y);
    R z;
}

VO a_repl(const C *s) {
    C *v, str[100]; A z;
    while (1) {
        printf(s, "%s\n");
        fgets(str, 100, stdin);
        v = strndup(str, strlen(str)-1); /* remove carriage return */
        println(z = eval(v));
    }
}
