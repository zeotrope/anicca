#ifndef _ADVERB_H
#define _ADVERB_H

#define ADEF(id, f1, f2, f, l, m, r) \
    func_def(id, ADV, f1, f2, f, NULL, NULL, l, m, r, 0)

#define ADERV(id, df1, df2, f, l, m, r) \
    derv_def(id, VERB, df1, df2, f, NULL, NULL, l, m, r, 0)

#define ADV_PROLOG \
    A f = VF(v); AF1 f1 = VF1(f); AF2 f2 = VF2(f);  A z;

MONAD(slash);
DMONAD(reduce);

#endif
