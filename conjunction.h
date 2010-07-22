#ifndef _CONJUNCTION_H
#define _CONJUNCTION_H

#define CDEF(id, f1, f2, f, g, l, r, m) \
    func_def(id, CONJ, f1, f2, f, g, NULL, l, r, m, 0)

#define CDERV(id, df1, df2, f, g, l, r, m) \
    derv_def(id, VERB, df1, df2, f, g, NULL, l, r, m, 0)

#define CONJ_PROLOG \
    A f = VF(v); A g = VG(v); AF1 f1 = VF1(f); AF2 f2 = VF2(f); AF1 g1 = VF1(g); \
    AF2 g2 = VF2(g);

DYAD(amper);
DMONAD(bond);
DDYAD(dbond);
DMONAD(compose);
DDYAD(dcompose);

DYAD(at);
DMONAD(atop);
DDYAD(datop);

#endif
