#ifndef _TEST_H
#define _TEST_H

struct {
    const C *input;
    A expected;
} testcases[] = {
    { "(1.5 9e2 3)", NULL },
    { "1",           NULL },
};

B eq_shape(A x, A y);
B eq(A x, A y);
B run_test(const C * input, A expected);
VO testcases_init(VO);

#endif
