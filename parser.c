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
    I b, c, d, e, p, q, n = AN(tokens), j = n-4, m = j, *t;
    PF action;
    A *stack = (A *)AV(tokens), *top, z;

    do {
        top = &stack[j];
        printf("m: %d j: %d ", m, j); print(tokens);

        for (c = 0; c < CASES; c++) {
            t = grammar[c].t;
            if (AT(top[0])&t[0] && AT(top[1])&t[1] &&
                AT(top[2])&t[2] && AT(top[3])&t[3]) { break; }
        }
        
        if (c < CASES) {
            b = grammar[c].b; p = b+j;
            e = grammar[c].e; q = e+j;

            printf(" b: %d e: %d c: %d\n", p, q, c);
            
            action = grammar[c].act;
            top[e] = action(b, e, top);
            DO(p, stack[--q] = stack[--p]);
            m -= e-b;
            j += e;
        }
        else {
            j--;
        }
        printf("\n");
    } while (j >= 0 && m > 2);

    printf("%d %d\n", m, j);
    println(tokens);
    z = stack[j];

    return z;
}
