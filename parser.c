#include "anicca.h"
#include "util.h"
#include "symbol.h"
#include "parser.h"

ACTION(monad)   { R df1(stack[e],    stack[b]);                }
ACTION(dyad)    { R df2(stack[b],    stack[e],   stack[b+1]);  }
ACTION(adverb)  { R ddf1(stack[b],   stack[e]);                }
ACTION(conjun)  { R ddf2(stack[b],   stack[e],   stack[b+1]);  }
ACTION(trident) { R dfrk(stack[b],   stack[b+1], stack[e]);    }
ACTION(bident)  { R dhk(stack[b],    stack[e]);                }
ACTION(is)      { R symbis(stack[b], stack[e],   global);      }
ACTION(paren)   { R stack[b+1];                                }
ACTION(move)    { A x=stack[b], y=stack[e];
    R AT(x)&NAME ? (ASGN&AT(y) ? x : symbfind(x,global)) : x;
}

#define CASES 9

static PT grammar[CASES]={
    {EDGE,      VERB,      NOUN, ANY,       monad,   1, 2}, /* Monad   */
    {EDGE|AVN,  VERB,      VERB, NOUN,      monad,   2, 3}, /* Monad   */
    {EDGE|AVN,  NOUN,      VERB, NOUN,      dyad,    1, 3}, /* Dyad    */
    {EDGE|AVN,  VERB|NOUN, ADV,  ANY,       adverb,  1, 2}, /* Adverb  */
    {EDGE|AVN,  VERB|NOUN, CONJ, VERB|NOUN, conjun,  1, 3}, /* Conjun  */
    {EDGE|AVN,  VERB|NOUN, VERB, VERB,      trident, 1, 3}, /* Trident */
    {EDGE,      CAVN,      CAVN, ANY,       bident,  1, 2}, /* Bident  */
    {NAME|NOUN, ASGN,      CAVN, ANY,       is,      0, 2}, /* Is      */
    {LPAR,      CAVN,      RPAR, ANY,       paren,   0, 2}  /* Paren   */
};

/* parse
     input: Array of tokens to be parsed, output of function tokens.
     output: An array, the result of a successful parse. */
A parse(A tokens) {
    PF action;
    A *top, *stack = AAV(tokens), z;
    I  b, c, d, e, i, p, q, n=AN(tokens)-4, j=n,*t;

    do {
        top=&stack[j];
#ifdef DEBUG
        printf("n: %d j: %d ",n,j); print(tokens);
#endif
        for (c=0; c<CASES; c++) {
            t = grammar[c].t;
            if (AT(top[0])&t[0] && AT(top[1])&t[1] &&
                AT(top[2])&t[2] && AT(top[3])&t[3]) { break; }
        }

        if (c<CASES) {
            b=grammar[c].b; p=j+b;
            e=grammar[c].e; q=j+e;
#ifdef DEBUG
            printf(" b: %d e: %d c: %d\n",p,q,c);
#endif
            action = grammar[c].act;
            top[e] = action(b,e,top);
            DO(p, stack[--q]=stack[--p]);
            n-=e-b; j+=e;
        }
        else {
            do {
                i=MAX(0,j-1);
                stack[i]=move(i,j,stack);
                j--;
            } while (NEXC&AT(stack[j]));
        }
#ifdef DEBUG
        printf("\n");
#endif
    } while (j>=0 && n>2);
#ifdef DEBUG
    printf("n: %d j: %d ",n,j);
    println(tokens);
#endif
    if (n>2) { a_signal(ERSYNTAX); };
    z = stack[j]; R z;
}
