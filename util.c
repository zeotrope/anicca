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
    C *cv; I *iv; D *fv; V *vv; A *bv;

    if (!y) { printf("NULL"); return; }

    switch (AT(y)) {
    case BOOL: { cv = BAV(y); DO(AN(y), printf("%d ", (I)cv[i])); break; }
    case CHAR: { cv = CAV(y); DO(AN(y), printf("%c", cv[i]));     break; }
    case INT:  { iv = IAV(y); DO(AN(y), printf("%d ", iv[i]));    break; }
    case FLT:  { fv = DAV(y); DO(AN(y), printf("%lf ", fv[i]));   break; }
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
    zero = sint(0); one = sint(1);
    mark = ga(MARK, 0, 0, NULL);
    lpar = ga(LPAR, 0, 0, NULL);
    rpar = ga(RPAR, 0, 0, NULL);
}

A eval(const C *str) {
    A w, y, z;
    w = gstr(strlen(str)+1, str);
    y = tokens(w);
    z = parse(y);
    a_free(w); a_free(y);
    return z;
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
