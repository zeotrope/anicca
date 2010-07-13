#ifndef _ADVERB_H
#define _ADVERB_H

#define ADEF(id, f1, f2, f, l, m, r) \
    func_def(id, ADV, f1, f2, f, NULL, NULL, l, m, r, 0)

#define ADERV(id, f1, f2, f, l, m, r) \
    func_def(id, VERB, f1, f2, f, NULL, NULL, l, m, r, 0)

#define ADVERB_PROLOG \
    A f = VF(y); AF1 f1 = f ? VF1(f) : NULL; AF2 f2 = f ? VF2(f) : NULL

MONAD(slash);
MONAD(reduce);

#endif
