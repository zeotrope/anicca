#include <stdio.h>
#include <stdlib.h>

#include "anicca.h"
#include "error.h"
#include "memory.h"
#include "verb.h"
#include "util.h"

MONAD(tally) {
    MONAD_PROLOG;
    z = gen_array(INT, 0, 1, NULL);
    v = (I *)AV(z);
    *v = AN(y);
    return z;
}

DYAD(copy) {
    DYAD_PROLOG;
    return z;
}

MONAD(fact) {
    MONAD_PROLOG; I n = yv[0], r = 1;
    ASSERT(AT(y)&INT && (n>=0), ERDOM);
    z = gen_array(INT, 0, 1, NULL);
    v = (I *)AV(z);
    DO(n, r *= n--);
    *v = r;
    return z;
}

DYAD(outof) {
    DYAD_PROLOG;
    z = gen_array(INT, 0, 1, NULL);
    return z;
}

MONAD(signum) {
    MONAD_PROLOG; I r;
    ASSERT(AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = (I *)AV(z);
    DO(yn,
       r = yv[i];
       v[i] = r > 0 ? 1 : r < 0 ? -1 : 0);
    return z;
}

DYAD(times) {
    DYAD_PROLOG;
    ASSERT(AT(x)&INT && AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = (I *)AV(z);
    DO(yn, v[i] = xv[i] * yv[i]);
    return z;
}

MONAD(conjugate) {
    MONAD_PROLOG;
    return z;
}

DYAD(plus) {
    DYAD_PROLOG;
    ASSERT(AT(x)&INT && AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = (I *)AV(z);
    DO(yn, v[i] = xv[i] + yv[i]);
    return z;
}

MONAD(negate) {
    MONAD_PROLOG;
    z = gen_array(INT, AR(y), yn, AS(y));
    v = (I *)AV(z);
    DO(yn, v[i] = - yv[i]);
    return z;
}

DYAD(minus) {
    DYAD_PROLOG;
    ASSERT(AT(x)&INT && AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = (I *)AV(z);
    DO(yn, v[i] = xv[i] - yv[i]);
    return z;
}

MONAD(iota) {
    MONAD_PROLOG; I n = yv[0];
    z = gen_array(INT, AR(y), n, AS(y));
    v = (I *)AV(z);
    DO(n, v[i] = i);
    return z;
}

MONAD(tail) {
    MONAD_PROLOG;
    z = gen_array(INT, 0, 1, NULL);
    *(I *)AV(z) = yv[AN(y)-1];
    return z;
}
