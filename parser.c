#include <stdio.h>
#include <stdlib.h>

#include "anicca.h"
#include "parser.h"

ACTION(monad) {
    A y, v, z;
    y = stack[e];
    v = stack[b];
    z = VEAV(v)->f1(y);
    return z;
}

ACTION(dyad) {
    A x, y, v, z;
    x = stack[b];
    y = stack[e];
    v = stack[b+1];
    z = VEAV(v)->f2(x, y);
    return z;
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
    PF action;
    A *stack = (A *)AV(tokens), *top, z;

    top = &stack[m];
    DO(3, top--); /* testing */

    for (c = 0; c < CASES; c++) {
        t = grammar[c].t;
        if (AT(top[0])&t[0] && AT(top[1])&t[1] &&
            AT(top[2])&t[2] && AT(top[3])&t[3]) { break; }
    }

    if (c < CASES) {
        b = grammar[c].b;
        e = grammar[c].e;
        action = grammar[c].act;
        top[e] = action(b, e, top);
        DO(b, top[--e] = top[--b]);
    }
    else {
        top--;
    }

    return z;
}
