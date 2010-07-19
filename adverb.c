#include <stdlib.h>

#include "anicca.h"
#include "memory.h"
#include "char.h"
#include "function.h"
#include "verb.h"
#include "adverb.h"

MONAD(slash) {
    A z;
    if (AT(y)&VERB) {
        return ADERV(CSLASH, reduce, NULL, y, VLR(y), VMR(y), VRR(y));
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
