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
    }
    printf("\n");
}

V a_init(V) {
    mark = gen_array(MARK, 0, 0, NULL);
}

int main() {
    A x, y, z;
    char *s = "1 2 3";
    x = array_str(strlen(s)+1, s);
    y = token_index(x);
    print(y);
    return 0;
}
