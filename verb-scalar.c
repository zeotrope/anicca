#include <math.h>

#include "anicca.h"
#include "scalar1.h"
#include "verb-atomic.h"
#include "verb-scalar.h"

MONAD(fact) { A z=va1(CBANG,y); R z; }

DYAD(outof) { A z; z=divide(fact(y),times(fact(x),fact(minus(y,x)))); R z; }

MONAD(reciprocal) { A z=divide(one,y); R z; }

DYAD(divide) { A z=va2(CPERC,x,y); R z; }

MONAD(signum) { A z;
    switch (AT(y)) {
    case BOOL: z=ca(y);               break;
    case INT:  z=sex1(y,INT,isignum); break;
    case FLT:  z=sex1(y,INT,dsignum); break;
    }
    R z;
}

DYAD(times) { A z=va2(CSTAR,x,y); R z; }

MONAD(square) { A z=times(y,y); R z;  }

MONAD(conjugate) { A z; R z; }

DYAD(plus) { A z=va2(CPLUS,x,y); R z; }

MONAD(duble) { A z=plus(y,y); R z; }

MONAD(negate) { A z=minus(zero,y); R z; }

DYAD(minus) { A z=va2(CSUBT,x,y); R z; }

MONAD(not) { A z=minus(one,y); R z; }

DYAD(lthan) { A z=va2(CLT,x,y); R z; }

MONAD(decrement) { A z=minus(y,one); R z; }

DYAD(equal) { A z=va2(CEQ,x,y); R z; }

DYAD(gthan) { A z=va2(CGT,x,y); R z; }

MONAD(increment) { A z=plus(y,one); R z; }

MONAD(roll) { A z; R z; }

MONAD(expntl) { MONAD_PROLOG; I *v=IAV(y); D *d;
    z=ga(FLT,yr,yn,ys); d=DAV(z);
    DO(yn, v[i]=exp((D)v[i]));
    R z;
}

DYAD(power) { A z=va2(CPOW,x,y); R z; }

MONAD(imaginary) { A z=times(zone,y); R z; }

DYAD(complex) { A z=plus(x,imaginary(y)); R z; }

MONAD(pitimes) { A z=va1(CCIRC,y); R z; }

DYAD(circle) { A z; R z; }

DYAD(residue) { A z; R z; }
