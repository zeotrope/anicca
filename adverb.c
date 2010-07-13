#include <stdlib.h>

#include "anicca.h"
#include "char.h"
#include "function.h"
#include "adverb.h"

MONAD(slash) {
    if (AT(y)==VERB) {
        return ADERV(CSLASH, reduce, NULL, y, VLR(y), VMR(y), VRR(y));
    }
}

MONAD(reduce) {
    ADVERB_PROLOG;
}
