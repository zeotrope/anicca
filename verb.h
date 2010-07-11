#ifndef _VERB_H
#define _VERB_H

#define MONAD_PROLOG \
    I yn = AN(y), *v, *yv = (I *)AV(y); A z
#define DYAD_PROLOG \
    I xn = AN(x), yn = AN(y), *v, *xv = (I *)AV(x), *yv = (I *)AV(y); A z

MONAD(fact);
DYAD(outof);

MONAD(negate);
DYAD(minus);

MONAD(iota);

#endif
