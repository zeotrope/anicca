#include <stdio.h>
#include <string.h>
#include "anicca.h"
#include "memory.h"
#include "lexer.h"
#include "verb.h"
#include "util.h"

V print(A y) {
    if (!y) {
        printf("NULL");
        return;
    }
    NOUN_SWITCH(AT(y),
                DO(AN(y), printf("%d ", bv[i])),
                DO(AN(y), printf("%d ", cv[i])),
                DO(AN(y), printf("%d ", iv[i])),
                DO(AN(y), printf("%f ", fv[i])),
                DO(AN(y), printf("%fj%f ", ZR(zv[i]), ZI(zv[i]))),
                /* TODO?: fancy line drawings */
                DO(AN(y), printf("(<"); print(bv[i]);
                   printf(")%s", (i+1 == AN(y))?"":",")),
                printf("MARK"),
                printf("????"));
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
    char *s = "1.5 9e2 3";

    a_init();

    x = array_str(strlen(s)+1, s);
    y = token_index(x);
    println(y);
    z = tokens(y, x);
    println(z);
    return 0;
}
