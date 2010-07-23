#include <stdio.h>
#include <stdlib.h>

#include "anicca.h"
#include "function.h"
#include "parser.h"

ACTION(monad)  { return df1(stack[e], stack[b]);              }
ACTION(dyad)   { return df2(stack[b], stack[e], stack[b+1]);  }
ACTION(adverb) { return df1(stack[b], stack[e]);              }
ACTION(conjun) { return df2(stack[b], stack[e], stack[b+1]);  }
ACTION(fork)   { return dfrk(stack[b], stack[b+1], stack[e]); }
ACTION(bident) { return dhk(stack[b], stack[e]);              }
ACTION(is)     { A z; return z;                               }
ACTION(paren)  { return stack[b+1];                           }

A parse(A tokens) {
    I b, c, d, e, p, q, n = AN(tokens), j = n-4, m = j, *t;
    PF action;
    A *stack = (A *)AV(tokens), *top, z;

    do {
        top = &stack[j];
        /* printf("m: %d j: %d ", m, j); print(tokens); */
        for (c = 0; c < CASES; c++) {
            t = grammar[c].t;
            if (AT(top[0])&t[0] && AT(top[1])&t[1] &&
                AT(top[2])&t[2] && AT(top[3])&t[3]) { break; }
        }
        
        if (c < CASES) {
            b = grammar[c].b; p = b+j;
            e = grammar[c].e; q = e+j;
            /* printf(" b: %d e: %d c: %d\n", p, q, c); */
            action = grammar[c].act;
            top[e] = action(b, e, top);
            DO(p, stack[--q] = stack[--p]);
            m -= e-b;
            j += e;
        }
        else {
            j--;
        }
        /* printf("\n"); */
    } while (j >= 0 && m > 2);

    /* printf("m: %d j: %d\n", m, j); */
    /* println(tokens); */
    z = stack[j];

    return z;
}
