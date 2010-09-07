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
static I probe(A x, A symb, B is);
DYAD(symbfind);
MONAD(symblg);
DDYAD(symbis);

A local;
A global;

#endif
