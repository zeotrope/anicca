#include <stdio.h>
#include <string.h>
#include "anicca.h"
#include "memory.h"
#include "lexer.h"
#include "verb.h"

V print(A y) {
    C *cv;
    I *iv;
    D *fv;
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
    case MARK: {
        printf("MARK");
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
}

int main() {
    A x, y, z;
    char *s = "1.5 9 3";

    a_init();

    x = array_str(strlen(s)+1, s);
    y = token_index(x);
    println(y);
    z = tokens(y, x);
    println(z);
    return 0;
}
