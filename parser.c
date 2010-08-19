#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "error.h"
#include "function.h"
#include "parser.h"

ACTION(monad)  { R df1(stack[e],  stack[b]);               }
ACTION(dyad)   { R df2(stack[b],  stack[e],   stack[b+1]); }
ACTION(adverb) { R df1(stack[b],  stack[e]);               }
ACTION(conjun) { R df2(stack[b],  stack[e],   stack[b+1]); }
ACTION(fork)   { R dfrk(stack[b], stack[b+1], stack[e]);   }
ACTION(bident) { R dhk(stack[b],  stack[e]);               }
ACTION(is)     { A z; R z;                                 }
ACTION(paren)  { R stack[b+1];                             }

#define CASES 9

static PT grammar[CASES] = {
    {EDGE,      VERB,      NOUN, ANY,       monad,  1, 2}, /* Monad  */
    {EDGE|AVN,  VERB,      VERB, NOUN,      monad,  2, 3}, /* Monad  */
    {EDGE|AVN,  NOUN,      VERB, NOUN,      dyad,   1, 3}, /* Dyad   */
    {EDGE|AVN,  VERB|NOUN, ADV,  ANY,       adverb, 1, 2}, /* Adverb */
    {EDGE|AVN,  VERB|NOUN, CONJ, VERB|NOUN, conjun, 1, 3}, /* Conjun */
    {EDGE|AVN,  VERB|NOUN, VERB, VERB,      fork,   1, 3}, /* Fork   */
    {EDGE,      CAVN,      CAVN, ANY,       bident, 1, 2}, /* Bident */
    {NAME|NOUN, ASGN,      CAVN, ANY,       is,     0, 2}, /* Is     */
    {LPAR,      CAVN,      RPAR, ANY,       paren,  0, 2}  /* Paren  */
};

/*
   parse
   input: Array of tokens to be parsed, output of function tokens.
   output: An array, the result of a successful parse.
*/
A parse(A tokens) {
    I  b, c, d, e, p, q, n = AN(tokens), j = n-4, m = j,*t;
    PF action;
    A *top, *stack = AAV(tokens), z;

    do {
        top = &stack[j];
        /*printf("m: %d j: %d ", m, j); print(tokens);*/
        for (c=0; c<CASES; c++) {
            t = grammar[c].t;
            if (AT(top[0])&t[0] && AT(top[1])&t[1] &&
                AT(top[2])&t[2] && AT(top[3])&t[3]) { break; }
        }

        if (c<CASES) {
            b = grammar[c].b; p = b+j;
            e = grammar[c].e; q = e+j;
            /*printf(" b: %d e: %d c: %d\n", p, q, c);*/
            action = grammar[c].act;
            top[e] = action(b, e, top);
            DO(p, stack[--q] = stack[--p]);
            m -= e-b; j += e;
        }
        else { j--; }
        /*printf("\n");*/
    } while (j>=0 && m>2);
    /*printf("m: %d j: %d\n", m, j);
      println(tokens);*/
    if (m>2) { a_signal(ERSYNTX); };
    z = stack[j]; R z;
}
