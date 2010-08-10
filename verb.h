#ifndef _VERB_H
#define _VERB_H

#define SF1(name, zt, yt, exp) \
    VO name(zt *z, yt *y) { *z=(exp); }

#define SF2(name, zt, yt, exp) \
    VO name(zt *z, yt *x, yt *y) { *z=(exp); }

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

VO bplus(I *, I *, I *);
VO bplus2(I *,B *, B *);
VO iplus(D *, I *, I *);
VO dplus(D *, D *, D *);
DYAD(plus);

MONAD(duble);
DYAD(append);
MONAD(negate);
DYAD(minus);
DYAD(lthan);
DYAD(equal);
DYAD(gthan);
MONAD(iota);
MONAD(expntl);
MONAD(same);
DYAD(left);
DYAD(right);
DYAD(residue);
MONAD(tail);

#endif
