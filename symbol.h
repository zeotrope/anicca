#ifndef _SYMBOL_H
#define _SYMBOL_H

typedef struct _symbol {
    A name;
    A value;
} SY;

#define SYAV(a) ((SY *)AV(a))
#define SYN(s)  ((s)->name)
#define SYV(s)  ((s)->value)

B symbinit(VO);
B vldnm(I n, C *s);
static I probe(A y, A symb, B is);
DYAD(symbfind);
MONAD(symblg);
static I nmclr(A y, A symb);
DDYAD(symbis);

A local;
A global;

#endif
