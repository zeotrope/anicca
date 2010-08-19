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
    z = ADERV(CFWSL, insert, table, y, VLR(v), VMR(v), VRR(v));
    R z;
}

DMONAD(insert) { A z; R z; }

DDYAD(table) { A z; R z; }

MONAD(tilde) {
    V *v; A z;
    ASSERT(AT(y)&VERB, ERDOM);
    v = VAV(y);
    z = ADERV(CTILDE, reflex, passive, y, VLR(v), VMR(v), VRR(v));
    R z;
}

DMONAD(reflex) { DECL_F; z = df2(y, y, f); R z; }

DDYAD(passive) { DECL_F; z = df2(y, x, f); R z; }
