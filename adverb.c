#include <stdlib.h>

#include "anicca.h"
#include "memory.h"
#include "char.h"
#include "function.h"
#include "verb.h"
#include "adverb.h"

MONAD(slash) {
    A z;
    V *v;
    if (AT(y)&VERB) {
        v = VAV(y);
        z = ADERV(CSLASH, reduce, NULL, y, VLR(v), VMR(v), VRR(v));
    }
    return z;
}

DMONAD(reduce) {
    A z;
    I n = AN(y);
    z = tail(y);
    if (n==1) { return z; }
    return z;
}
