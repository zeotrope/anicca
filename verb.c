#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "anicca.h"
#include "char.h"
#include "error.h"
#include "memory.h"
#include "function.h"
#include "verb.h"
#include "verb-scalar1.h"
#include "verb-atomic.h"
#include "util.h"

MONAD(fact) { MONAD_PROLOG;
    I temp, r;
    ASSERT(AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn, r = 1; temp = yv[i];
       DO(temp, r *= temp--);
       v[i] = r;
    );
    return z;
}

DYAD(outof) { A z;
    z = divide(fact(y), times(fact(x), fact(minus(y, x))));
    return z;
}

MONAD(tally) { A z; z = scalar_int(AN(y)); return z; }

DYAD(copy) { DYAD_PROLOG;
    I n = 0, itm, cnt;
    ASSERT(xn==yn, ERLEN );
    DO(xn, n += xv[i]);
    z = gen_array(INT, AR(y), n, AS(y));
    v = IAV(z);
    DO(xn, cnt = xv[i]; itm = yv[i];
       if (cnt>0) { DO(cnt, *v++ = itm); }
    );
    return z;
}

MONAD(reciprocal) { A z = divide(one, y); return z; }

DYAD(divide) { A z = va2(CFWSL, x, y); return z; }

MONAD(signum) { A z;
    switch (AT(y)) {
    case BOOL: z = copy_array(y);         break;
    case INT:  z = sex1(y, INT, isignum); break;
    case FLT:  z = sex1(y, INT, dsignum); break;
    }
    return z;
}

DYAD(times) { A z = va2(CSTAR, x, y); return z; }

MONAD(square) { A z = times(y, y); return z;  }

MONAD(conjugate) { MONAD_PROLOG;
    return z;
}

DYAD(plus) { A z = va2(CPLUS, x, y); return z; }

MONAD(duble) { A z = plus(y, y); return z; }

DYAD(append) {
    I xt = AT(x), yt = AT(y), xn = AN(x), yn = AN(y), zn = yn + xn, k;
    C *xv = CAV(x), *yv = CAV(y), *v;
    A z;
    if (xt==yt) {
        z = gen_array(yt, AR(y), zn, AS(y));
        v = CAV(z); k = type_size(yt);
        memcpy(v, xv, k*xn);
        v += k*xn;
        memcpy(v, yv, k*yn);
    } else { a_signal(ERDOM); }
    return z;
}

MONAD(negate) { A z = minus(zero, y); return z; }

DYAD(minus) { A z = va2(CSUBT, x, y); return z; }

MONAD(not) { A z = minus(one, y); return z; }

DYAD(link) {
    A z; return z;
}

MONAD(box) { A z = gen_array(BOX, 0, 1, NULL); *AAV(z) = y; return z; }

DYAD(lthan) { A z = va2(CLT, x, y); return z; }

MONAD(decrement) { A z = minus(y, one); return z; }

DYAD(equal) { A z = va2(CEQ, x, y); return z; }

MONAD(unbox) { A z;
    return z;
}

DYAD(gthan) { A z = va2(CGT, x, y); return z; }

MONAD(increment) { A z = plus(y, one); return z; }

MONAD(roll) {
    A z; return z;
}

DYAD(deal) {
    A z; return z;
}

MONAD(indices) { MONAD_PROLOG;
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    return z;
}

MONAD(expntl) {
    I yn = AN(y), *yv = IAV(y);
    A z = gen_array(FLT, AR(y), yn, AS(y)); D *v = DAV(z);
    DO(yn, v[i] = exp((D)yv[i]));
    return z;
}

MONAD(iota) { A z;
    I yr = AR(y), n = *IAV(y), *v;
    z = gen_array(INT, 1, n, AS(y));
    v = IAV(z);
    DO(n, v[i] = i);
    return z;
}

MONAD(same) { A z = copy_array(y); return z; }

DYAD(left) { A z = copy_array(x); return z; }

DYAD(right) { A z = copy_array(y); return z; }

DYAD(residue) {
    A z; return z;
}

MONAD(tail) { A z;
    return z;
}
