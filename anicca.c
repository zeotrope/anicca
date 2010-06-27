#include <stdio.h>
#include <string.h>

#include "anicca.h"
#include "char.h"
#include "memory.h"
#include "verb.h"
#include "primitive.h"
#include "lexer.h"

V print(A y) {
    C *cv;
    I *iv;
    D *fv;
    VE *vv;
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
    case VERB: {
        vv = VEAV(y);
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

V println(A y) {
    print(y);
    printf("\n");
}

V a_init(V) {
    mark = gen_array(MARK, 0, 0, NULL);
    lpar = gen_array(LPAR, 0, 0, NULL);
    rpar = gen_array(RPAR, 0, 0, NULL);
}

int main() {
    C *s = "(!1)";
    A x, y, z;

    a_init();
    x = array_str(strlen(s)+1, s);
    y = token_index(x);
    z = tokens(y, x);
    println(z);

    return 0;
}
