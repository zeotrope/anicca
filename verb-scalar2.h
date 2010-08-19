#ifndef _VERB_SCALAR2_H
#define _VERB_SCALAR2_H

#define SF2(name, zt, yt, exp) \
    VO name(zt *z, yt *x, yt *y) { *z=(exp); }

#define DECL_SF2(name, zt, yt) \
    VO name(zt *z, yt *x, yt* y)

DECL_SF2(bdivide, D, B);
DECL_SF2(idivide, D, I);
DECL_SF2(ddivide, D, D);
DECL_SF2(jdivide, Z, Z);

DECL_SF2(btimes, B, B);
DECL_SF2(itimes, I, I);
DECL_SF2(dtimes, D, D);
DECL_SF2(jtimes, Z, Z);

DECL_SF2(bplus, I, B);
DECL_SF2(iplus, I, I);
DECL_SF2(dplus, D, D);
DECL_SF2(jplus, Z, Z);

DECL_SF2(bminus, I, B);
DECL_SF2(iminus, I, I);
DECL_SF2(dminus, D, D);

DECL_SF2(blthan, B, B);
DECL_SF2(ilthan, B, I);
DECL_SF2(dlthan, B, D);

DECL_SF2(bpower, B, B);
DECL_SF2(ipower, D, I);
DECL_SF2(dpower, D, D);

#endif
