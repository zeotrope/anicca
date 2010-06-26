#include <stdio.h>
#include <stdlib.h>
#include "anicca.h"
#include "parser.h"

ACTION(monad) {
    A z; return z;
}

ACTION(dyad) {
    A z; return z;
}

ACTION(adverb) {
    A z; return z;
}

ACTION(conjun) {
    A z; return z;
}

ACTION(fork) {
    A z; return z;
}

ACTION(bident) {
    A z; return z;
}

ACTION(is) {
    A z; return z;
}

ACTION(paren) {
    A z; return z;
}

A parse(A tokens) {
    I b, c, e, n = AN(tokens), m = n-4, *t;
    A *stack = (A *)AV(tokens), *top, z;

    top = &stack[m];

    for (c = 0; c < CASES; c++) {
        t = grammar[c].t;
        if (AT(top[0])&t[0] && AT(top[1])&t[1] &&
            AT(top[2])&t[2] && AT(top[3])&t[3]) { break; }
    }

    if (c < CASES) {
        b = grammar[c].b;
        e = grammar[c].e;
    }
    else {
        top--;
    }

    return z;
}
