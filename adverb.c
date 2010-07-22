#include <stdlib.h>

#include "anicca.h"
#include "memory.h"
#include "char.h"
#include "function.h"
#include "verb.h"
#include "adverb.h"

MONAD(slash) {
    V *v;
    A z;
    if (AT(y)&VERB) {
        v = VAV(y);
        z = ADERV(CSLASH, insert, table, y, VLR(v), VMR(v), VRR(v));
    }
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
