#ifndef _CONJUNCTION_H
#define _CONJUNCTION_H

#define CDEF(id, f1, f2, f, g, l, r, m) \
    func_def(id, CONJ, f1, f2, f, g, NULL, l, r, m, 0)

#define CDERV(id, f1, f2, f, g, l, r, m) \
    func_def(id, VERB, f1, f2, f, g, NULL, l, r, m, 0)

#define CONJ_PROLOG \
    A f = VF(v); A g = VG(v); AF f1 = VF1(f); AF f2 = VF2(f); AF g1 = VF1(g); \
    AF g2 = VF2(g);                                                           \

#endif
