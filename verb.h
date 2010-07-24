#ifndef _VERB_H
#define _VERB_H

#define MONAD_PROLOG \
    I yn = AN(y), *v, *yv = (I *)AV(y); A z

#define DYAD_PROLOG \
    I xn = AN(x), yn = AN(y), *v, *xv = (I *)AV(x), *yv = (I *)AV(y); A z

MONAD(fact);
DYAD(outof);

MONAD(tally);
DYAD(copy);

MONAD(reciprocal);
DYAD(divide);

MONAD(signum);
DYAD(times);

MONAD(conjugate);
DYAD(plus);

MONAD(negate);
DYAD(minus);

MONAD(same);
DYAD(left);
DYAD(right);

MONAD(iota);

MONAD(tail);

#endif
