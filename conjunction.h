#ifndef _CONJUNCTION_H
#define _CONJUNCTION_H

#include "conj-rank.h"

#define CDEF(id, f1, f2, f, g, l, r, m) \
    fdef(id, CONJ, f1, f2, f, g, NULL, l, r, m, 0)

#define CDERV(id, df1, df2, f, g, l, r, m) \
    ddef(id, VERB, df1, df2, f, g, NULL, l, r, m, 0)

DYAD(amper);
DMONAD(bond);
DDYAD(bond2);
DMONAD(compose);
DDYAD(compose2);
DYAD(atsign);
DMONAD(atop);
DDYAD(atop2);
DMONAD(hook);
DDYAD(hook2);
DYAD(cartcol);
DMONAD(cpower);
DDYAD(cpower2);
DMONAD(folk);
DDYAD(folk2);

#endif
