#ifndef _VERB_SCALAR1_
#define _VERB_SCALAR1_

#define SF1(name, zt, yt, exp) \
    VO name(zt *z, yt *y) { *z=(exp); }

#define DECL_SF1(name, zt, yt) \
    VO name(zt *z, yt *y)

DECL_SF1(isignum, I, I);
DECL_SF1(dsignum, I, D);

#endif
