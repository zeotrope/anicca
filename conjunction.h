#ifndef _CONJUNCTION_H
#define _CONJUNCTION_H

#define CDEF(id, f1, f2, f, g, l, r, m) \
    func_def(id, CONJ, f1, f2, f, g, NULL, l, r, m, 0)

#define CDERV(id, df1, df2, f, g, l, r, m) \
    derv_def(id, VERB, df1, df2, f, g, NULL, l, r, m, 0)

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
DMONAD(power);
DDYAD(power2);
DMONAD(forrk);
DDYAD(forrk2);

#endif
