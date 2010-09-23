#include "anicca.h"
#include "verb.h"
#include "adverb.h"

MONAD(slash) { V *v=VAV(y); A z;
    ASSERT(AT(y)&VERB,ERDOM);
    z=ADERV(CFWSL,insert,table,y,VLR(v),VMR(v),VRR(v));
    R z;
}

DMONAD(insert) { A z; R z; }

DDYAD(table) { A z; R z; }

MONAD(tilde) { V *v=VAV(y); A z;
    ASSERT(AT(y)&VERB,ERDOM);
    z=ADERV(CTILDE,reflex,passive,y,VLR(v),VMR(v),VRR(v));
    R z;
}

DMONAD(reflex) { DECL_F; z=f2(y,y,f); R z; }

DDYAD(passive) { DECL_F; z=f2(y,x,f); R z; }
