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
    C *cv;
    I *iv;
    D *fv;
    V *vv;
    A *bv;

    if (!y) {
        printf("NULL");
        return;
    }
    switch (AT(y)) {
    case BOOL: {
        cv = (B *)AV(y);
        DO(AN(y), printf("%d ", (I)cv[i]));
        break;
    }
    case CHAR: {
        cv = (C *)AV(y);
        DO(AN(y), printf("%c", cv[i]));
        break;
    }
    case INT: {
        iv = (I *)AV(y);
        DO(AN(y), printf("%d ", iv[i]));
        break;
    }
    case FLT: {
        fv = (D *)AV(y);
        DO(AN(y), printf("%lf ", fv[i]));
        break;
    }
    case BOX: {
        bv = (A *)AV(y);
        /* TODO?: fancy line drawings */
        DO(AN(y), printf("(<"); print(bv[i]);
           printf(")%s", (i+1 == AN(y))?"":","));
        break;
    }
    case VERB: case ADV: case CONJ: {
        vv = VAV(y);
        printf("%c %d", vv->id, vv->id);
        break;
    }
    case MARK: {
        printf("MARK");
        break;
    }
    case LPAR: {
        printf("LPAR");
        break;
    }
    case RPAR: {
        printf("RPAR");
        break;
    }
    default: {
        printf("HUH?");
        break;
    }
    }
}

VO println(A y) {
    print(y);
    printf("\n");
}

VO a_init(VO) {
    mark = gen_array(MARK, 0, 0, NULL);
    lpar = gen_array(LPAR, 0, 0, NULL);
    rpar = gen_array(RPAR, 0, 0, NULL);
}

A eval(C *str) {
    A w, x, y, z;

    w = array_str(strlen(str)+1, str);
    x = token_index(w);
    y = tokens(x, w);
    z = parse(y);
    a_free(w); a_free(x); a_free(y);

    return z;
}
