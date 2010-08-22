#ifndef _VERB_H
#define _VERB_H

#define MONAD_PROLOG \
    I yn = AN(y), *v, *yv = IAV(y); A z

#define DYAD_PROLOG                                        \
    I xn = AN(x), xr = AR(x), yn = AN(y), yr = AR(y), vn;  \
    I *v, *xv = IAV(x), *yv = IAV(y);                      \
    A m, z

MONAD(fact);
DYAD(outof);
MONAD(tally);
DYAD(copy);
MONAD(reciprocal);
DYAD(divide);
MONAD(signum);
DYAD(times);
MONAD(square);
MONAD(conjugate);
DYAD(plus);
MONAD(duble);
DYAD(append);
MONAD(negate);
DYAD(minus);
MONAD(not);
MONAD(box);
DYAD(lthan);
MONAD(decrement);
DYAD(equal);
MONAD(unbox);
DYAD(gthan);
MONAD(increment);
MONAD(expntl);
DYAD(power);
MONAD(same);
DYAD(left);
DYAD(right);
DYAD(power);
MONAD(iota);
MONAD(imaginary);
DYAD(complex);
DYAD(residue);
MONAD(execute);
MONAD(tail);

#endif
