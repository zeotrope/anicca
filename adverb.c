#include <stdlib.h>

#include "anicca.h"
#include "error.h"
#include "memory.h"
#include "char.h"
#include "function.h"
#include "verb.h"
#include "adverb.h"

MONAD(slash) {
    V *v; A z;
    ASSERT(AT(y)&VERB, ERDOM);
    v = VAV(y);
    z = ADERV(CSLASH, insert, table, y, VLR(v), VMR(v), VRR(v));
    return z;
}

DMONAD(insert) {
    A z = tail(y);
    I r, n = AN(y), k = n-2;
    if (n==1) { return z; }
    return z;
}

DDYAD(table) {
    A z;
    return z;
}

MONAD(tilde) {
    V *v; A z;

    ASSERT(AT(y)&VERB, ERDOM);
    v = VAV(y);

    z = ADERV(CTILDE, reflex, passive, y, VLR(v), VMR(v), VRR(v));

    return z;
}

DMONAD(reflex) {
    DECL_F;

    z = df2(y, y, f);

    return z;
}

DDYAD(passive) {
    DECL_F;

    z = df2(y, x, f);

    return z;
}
