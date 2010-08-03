#ifndef _CONJUNCTION_H
#define _CONJUNCTION_H

#define CDEF(id, f1, f2, f, g, l, r, m) \
    func_def(id, CONJ, f1, f2, f, g, NULL, l, r, m, 0)

#define CDERV(id, df1, df2, f, g, l, r, m) \
    derv_def(id, VERB, df1, df2, f, g, NULL, l, r, m, 0)

DYAD(amper);
DMONAD(bond);
DDYAD(dbond);
DMONAD(compose);
DDYAD(dcompose);
DYAD(at);
DMONAD(atop);
DDYAD(datop);
DMONAD(chook);
DDYAD(dchook);
DYAD(powr);
DMONAD(cpower);
DDYAD(cdpower);
DMONAD(cfork);
DDYAD(dcfork);

#endif
