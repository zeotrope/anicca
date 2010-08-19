#include <stdio.h>

#include "anicca.h"
#include "memory.h"
#include "test.h"
#include "util.h"

B eq_shape(A x, A y) {
    if (AR(x) != AR(y)) R 0;
    if (AS(x) == AS(y)) R 1;
    if (AS(x) == NULL || AS(y) == NULL) R 0;
    DO(AR(x), if (AS(x)[i] != AS(y)[i]) R 0);

    R 1;
}

B eq(A x, A y) {
    if (x == y) R 1;
    if (x == NULL || y == NULL) R 0;
    if (AT(x) != AT(y) || AN(x) != AN(y) || !eq_shape(x, y))
        R 0;
    /* TODO: make it work for rank > 1 */
    NOUN_SWITCH(AT(x),
                DO(AN(x), B *xbv = AV(x); B *ybv = AV(y);
                   if (xbv[i] != ybv[i]) R 0),
                DO(AN(x), C *xcv = AV(x); C *ycv = AV(y);
                   if (xcv[i] != ycv[i]) R 0),
                DO(AN(x), I *xiv = AV(x); I *yiv = AV(y);
                   if (xiv[i] != yiv[i]) R 0),
                DO(AN(x), D *xfv = AV(x); D *yfv = AV(y);
                   if (xfv[i] != yfv[i]) R 0),
                DO(AN(x), Z *xzv = AV(x); Z *yzv = AV(y);
                   if (ZR(xzv[i]) != ZR(yzv[i]) ||
                       ZI(xzv[i]) != ZI(yzv[i])) R 0),
                DO(AN(x), A *xbv = AV(x); A *ybv = AV(y);
                   if (!eq(xbv[i], ybv[i])) R 0),
                R 1,       /* MARK, no value */
                R 1,       /* LPAR, no value */
                R 1,       /* RPAR, no value */
                R 0);      /* unknown type, shouldn't happen */
    R 1;
}


B run_test(const C *input, A expected) {
    A z = eval(input);
    if (!eq(z, expected)) {
        printf("Test failed: %s\n", input);
        printf(" got: ");
        println(z);
        printf(" expected: ");
        println(expected);
        R 0;
    }
    R 1;
}

VO testcases_init(VO) {
    D e0[] = { 1.5, 900, 3 };
    I e1[] = { 1           };
    
    testcases[0].expected = gtest_array(3, lpar, gfarray(e0, LENGTHOF(e0)), rpar);
    testcases[1].expected = gtest_array(1, giarray(e1, LENGTHOF(e1)));
}
