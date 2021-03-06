#ifndef _ADVERB_H
#define _ADVERB_H

#define ADEF(id, f1, f2, f, l, m, r) \
    fdef(id, ADV, f1, f2, f, NULL, NULL, l, m, r, 0)

#define ADERV(id, df1, df2, f, l, m, r) \
    ddef(id, VERB, df1, df2, f, NULL, NULL, l, m, r, 0)

MONAD(slash);
DMONAD(insert);
DDYAD(table);
MONAD(tilde);
DMONAD(reflex);
DDYAD(passive);

#endif
