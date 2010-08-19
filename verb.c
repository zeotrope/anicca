#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "anicca.h"
#include "char.h"
#include "error.h"
#include "memory.h"
#include "util.h"
#include "convert.h"
#include "function.h"
#include "lexer.h"
#include "parser.h"
#include "verb-scalar1.h"
#include "verb-atomic.h"
#include "verb.h"

MONAD(fact) { MONAD_PROLOG;
    I temp, r;
    ASSERT(AT(y)&INT, ERDOM);
    z = ga(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn, r = 1; temp = yv[i];
       DO(temp, r *= temp--);
       v[i] = r;
    );
    R z;
}

DYAD(outof) { A z; z = divide(fact(y),times(fact(x),fact(minus(y,x)))); R z; }

MONAD(tally) { A z; z = sint(AN(y)); R z; }

DYAD(copy) { DYAD_PROLOG;
    I n = 0, itm, cnt;
    ASSERT(xn==yn, ERLEN );
    DO(xn, n += xv[i]);
    z = ga(INT, AR(y), n, AS(y));
    v = IAV(z);
    DO(xn, cnt = xv[i]; itm = yv[i];
       if (cnt>0) { DO(cnt, *v++ = itm); }
    );
    R z;
}

MONAD(reciprocal) { A z = divide(one, y); R z; }

DYAD(divide) { A z = va2(CPERC,x,y); R z; }

MONAD(signum) { A z;
    switch (AT(y)) {
    case BOOL: z = ca(y);         break;
    case INT:  z = sex1(y, INT, isignum); break;
    case FLT:  z = sex1(y, INT, dsignum); break;
    }
    R z;
}

DYAD(times) { A z = va2(CSTAR,x,y); R z; }

MONAD(square) { A z = times(y,y); R z;  }

MONAD(conjugate) { A z; R z; }

DYAD(plus) { A z = va2(CPLUS,x,y); R z; }

MONAD(duble) { A z = plus(y, y); R z; }

DYAD(append) {
    I xt=AT(x), yt=AT(y), xr=AR(x), yr=AR(y);
    I xn=AN(x), yn=AN(y), *xs=AS(x), *ys=AS(y);
    I t=MAX(xt,yt), r=MAX(xr,yr), zn=yn+xn, k;
    C *xv, *yv, *v; A p=x, q=y, z;
    if (xt&NUMERIC&&yt&NUMERIC && (xt!=yt)) {
        if (xt>yt) { q=conv(t, y); yt=t; }
        else       { p=conv(t, x); xt=t; }
    }
    xv=CAV(p); yv=CAV(q);
    if (xt==yt) {
        z = ga(t, r=(r!=0?r:1), zn, xr>yr ? xs : ys);
        v=CAV(z); k=ts(t);
        memcpy(v, xv, k*xn);
        v += k*xn;
        memcpy(v, yv, k*yn);
    } else { a_signal(ERDOM); }
    R z;
}

MONAD(negate) { A z = minus(zero, y); R z; }

DYAD(minus) { A z = va2(CSUBT,x,y); R z; }

MONAD(not) { A z = minus(one, y); R z; }

DYAD(link) { A z; R z; }

MONAD(box) { A z = sbox(y); R z; }

DYAD(lthan) { A z = va2(CLT,x,y); R z; }

MONAD(decrement) { A z = minus(y, one); R z; }

DYAD(equal) { A z = va2(CEQ,x,y); R z; }

MONAD(unbox) { A z = ca(*AAV(y)); R z; }

DYAD(gthan) { A z = va2(CGT,x,y); R z; }

MONAD(increment) { A z = plus(y, one); R z; }

MONAD(roll) { A z; R z; }

DYAD(deal) { A z; R z; }

MONAD(indices) { MONAD_PROLOG;
    z = ga(INT, AR(y), yn, AS(y));
    v = IAV(z);
    R z;
}

MONAD(expntl) {
    I yn = AN(y), *yv = IAV(y);
    A z = ga(FLT, AR(y), yn, AS(y)); D *v = DAV(z);
    DO(yn, v[i] = exp((D)yv[i]));
    R z;
}

MONAD(same) { A z = ca(y); R z; }

DYAD(left) { A z = ca(x); R z; }

DYAD(right) { A z = ca(y); R z; }

DYAD(power) { A z = va2(CPOW,x,y); R z; }

MONAD(iota) { A z;
    I yr = AR(y), n = *IAV(y), *v;
    z = ga(INT, 1, n, AS(y));
    v = IAV(z);
    DO(n, v[i] = i);
    R z;
}

MONAD(imaginary) { A z = times(zone,y); R z; }

DYAD(complex) { A z = plus(x,imaginary(y)); R z; }

DYAD(residue) { A z; R z; }

MONAD(execute) { A z = parse(tokens(y)); R z; }

MONAD(tail) { A z; R z; }
