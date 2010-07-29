#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "error.h"
#include "memory.h"
#include "verb.h"
#include "util.h"

MONAD(fact) { MONAD_PROLOG;
    I temp, r;
    ASSERT(AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn,
       r = 1;
       temp = yv[i];
       DO(temp, r *= temp--);
       v[i] = r;
    );
    return z;
}

DYAD(outof) { DYAD_PROLOG;
    z = divide(fact(y), times(fact(x), fact(minus(y, x))));
    return z;
}

MONAD(tally) { MONAD_PROLOG;
    z = gen_array(INT, 0, 1, NULL);
    v = IAV(z); *v = AN(y);
    return z;
}

DYAD(copy) { DYAD_PROLOG;
    return z;
}

MONAD(reciprocal) {
    I yn = AN(y), *yv = IAV(y); D *v; A z;
    ASSERT(AT(y)&INT, ERDOM)
    z = gen_array(FLT, AR(y), yn, AS(y));
    v = DAV(z);
    DO(yn, v[i] = 1/(D)yv[i]);
    return z;
}

DYAD(divide) {
    I yn = AN(y), *xv = IAV(x), *yv = IAV(y); D *v; A z;
    ASSERT(AT(x)&INT && AT(y)&INT, ERDOM);
    z = gen_array(FLT, AR(y), yn, AS(y));
    v = DAV(z);
    DO(yn, v[i] = xv[i]/(D)yv[i]);
    return z;
}

MONAD(signum) { MONAD_PROLOG;
    I r;
    ASSERT(AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn,
       r = yv[i];
       v[i] = r > 0 ? 1 : r < 0 ? -1 : 0);
    return z;
}

DYAD(times) { DYAD_PROLOG;
    ASSERT(AT(x)&INT && AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn, v[i] = xv[i] * yv[i]);
    return z;
}

MONAD(conjugate) { MONAD_PROLOG;
    return z;
}

DYAD(plus) { DYAD_PROLOG;
    ASSERT(AT(x)&INT && AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn, v[i] = xv[i] + yv[i]);
    return z;
}

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

MONAD(negate) { MONAD_PROLOG;
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn, v[i] = - yv[i]);
    return z;
}

DYAD(minus) { DYAD_PROLOG;
    ASSERT(AT(x)&INT && AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn, v[i] = xv[i] - yv[i]);
    return z;
}

MONAD(iota) { MONAD_PROLOG;
    I n = yv[0];
    z = gen_array(INT, AR(y), n, AS(y));
    v = IAV(z);
    DO(n, v[i] = i);
    return z;
}

MONAD(tail) { MONAD_PROLOG;
    z = gen_array(INT, 0, 1, NULL);
    *IAV(z) = yv[AN(y)-1];
    return z;
}

MONAD(same) {
    A z = y;
    return z;
}

DYAD(left) {
    A z = x;
    return z;
}

DYAD(right) {
    A z = y;
    return z;
}

DYAD(residue) { DYAD_PROLOG;
    ASSERT(AT(x)&INT && AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn, v[i] =  yv[i] % xv[i]);
    return z;
}
