#ifndef _VERB_H
#define _VERB_H

#define MONAD_PROLOG \
    I yn = AN(y), *v, *yv = IAV(y); A z

#define DYAD_PROLOG                                        \
    I xn = AN(x), xr = AR(x), yn = AN(y), yr = AR(y), vn;  \
    I *v, *xv = IAV(x), *yv = IAV(y);                      \
    A m, z

MONAD(tally);
DYAD(copy);
DYAD(append);
MONAD(box);
MONAD(unbox);
MONAD(same);
DYAD(left);
DYAD(right);
MONAD(iota);
MONAD(execute);
MONAD(tail);

#endif
