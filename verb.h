#ifndef _VERB_H
#define _VERB_H

#define MONAD_PROLOG \
    I yn = AN(y), *v, *yv = IAV(y); A z

#define DYAD_PROLOG \
    I xn = AN(x), yn = AN(y), *v, *xv = IAV(x), *yv = IAV(y); A z

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
DYAD(append);
MONAD(negate);
DYAD(minus);
DYAD(lthan);
DYAD(equal);
DYAD(gthan);
MONAD(iota);
MONAD(tail);
MONAD(same);
DYAD(left);
DYAD(right);
DYAD(residue);

#endif
