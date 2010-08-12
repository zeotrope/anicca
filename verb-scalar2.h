#ifndef _VERB_SCALAR2_
#define _VERB_SCALAR2_

#define SF2(name, zt, yt, exp) \
    VO name(zt *z, yt *x, yt *y) { *z=(exp); }

#define DECL_SF2(name, zt, yt) \
    VO name(zt *z, yt *x, yt* y)

DECL_SF2(bdivide,  I, I);
DECL_SF2(bdivide2, I, B);
DECL_SF2(idivide,  D, I);
DECL_SF2(ddivide,  D, D);

DECL_SF2(btimes,  I, I);
DECL_SF2(btimes2, I, B);
DECL_SF2(itimes,  D, I);
DECL_SF2(dtimes,  D, D);

DECL_SF2(bplus,  I, I);
DECL_SF2(bplus2, I, B);
DECL_SF2(iplus,  D, I);
DECL_SF2(dplus,  D, D);

DECL_SF2(bminus,  I, I);
DECL_SF2(bminus2, I, B);
DECL_SF2(iminus,  D, I);
DECL_SF2(dminus,  D, D);

DECL_SF2(blthan,  I, I);
DECL_SF2(blthan2, I, B);
DECL_SF2(ilthan,  D, I);
DECL_SF2(dlthan,  D, D);

#endif
