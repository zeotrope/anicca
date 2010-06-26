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
                DO(AN(y), B *bv = AV(y); printf("%d ", bv[i])),
                DO(AN(y), C *cv = AV(y); printf("%d ", cv[i])),
                DO(AN(y), I *iv = AV(y); printf("%d ", iv[i])),
                DO(AN(y), D *fv = AV(y); printf("%f ", fv[i])),
                DO(AN(y), Z *zv = AV(y); printf("%fj%f ", ZR(zv[i]), ZI(zv[i]))),
                /* TODO?: fancy line drawings */
                DO(AN(y), A *bv = AV(y); printf("(<"); print(bv[i]);
                   printf(")%s", (i+1 == AN(y))?"":",")),
                printf("MARK"),
                printf("LPAR"),
                printf("RPAR"),
                printf("????"));
}

V println(A y) {
    print(y);
    printf("\n");
}

B eq_shape(A x, A y) {
    if (AR(x) != AR(y)) return 0;
    if (AS(x) == AS(y)) return 1;
    if (AS(x) == NULL || AS(y) == NULL) return 0;
    DO(AR(x), if (AS(x)[i] != AS(y)[i]) return 0);

    return 1;
}

B eq(A x, A y) {
    if (x == y) return 1;
    if (x == NULL || y == NULL) return 0;
    if (AT(x) != AT(y) || AN(x) != AN(y) || !eq_shape(x, y))
        return 0;
    /* TODO: make it work for rank > 1 */
    NOUN_SWITCH(AT(x),
                DO(AN(x), B *xbv = AV(x); B *ybv = AV(y);
                   if (xbv[i] != ybv[i]) return 0),
                DO(AN(x), C *xcv = AV(x); C *ycv = AV(y);
                   if (xcv[i] != ycv[i]) return 0),
                DO(AN(x), I *xiv = AV(x); I *yiv = AV(y);
                   if (xiv[i] != yiv[i]) return 0),
                DO(AN(x), D *xfv = AV(x); D *yfv = AV(y);
                   if (xfv[i] != yfv[i]) return 0),
                DO(AN(x), Z *xzv = AV(x); Z *yzv = AV(y);
                   if (ZR(xzv[i]) != ZR(yzv[i]) ||
                       ZI(xzv[i]) != ZI(yzv[i])) return 0),
                DO(AN(x), A *xbv = AV(x); A *ybv = AV(y);
                   if (!eq(xbv[i], ybv[i])) return 0),
                return 1,       /* MARK, no value */
                return 1,       /* LPAR, no value */
                return 1,       /* RPAR, no value */
                return 0);      /* unknown type, shouldn't happen */
    return 1;
}

V a_init(V) {
    mark = gen_array(MARK, 0, 0, NULL);
    lpar = gen_array(LPAR, 0, 0, NULL);
    rpar = gen_array(RPAR, 0, 0, NULL);
}

B run_test(const char *input, A expected) {
    A x, y, z;

    x = array_str(strlen(input)+1, input);
    y = token_index(x);
    z = tokens(y, x);
    parse(z);

    if (!eq(z, expected)) {
        printf("Test failed: %s\n", input);
        printf(" got: ");
        println(z);
        printf(" expected: ");
        println(expected);

        return 0;
    }
    return 1;
}

struct {
    const char *input;
    A expected;
} testcases[] = {
    { "(1.5 9e2 3)", NULL },
    { "1", NULL },
};

V testcases_init() {
    D e0[] = { 1.5, 900, 3 };
    I e1[] = { 1 };

    testcases[0].expected = gen_test_array(3, lpar, gen_farray(e0, LENGTHOF(e0)), rpar);
    testcases[1].expected = gen_test_array(1, gen_iarray(e1, LENGTHOF(e1)));
}

int main() {

    a_init();
    testcases_init();

    DO(LENGTHOF(testcases),
       run_test(testcases[i].input, testcases[i].expected));

    return 0;
}
