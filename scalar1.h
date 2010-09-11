#ifndef _SCALAR1_H
#define _SCALAR1_H

#define SF1(name, zt, yt, exp) \
    VO name(zt *z, yt *y) { *z=(exp); }

#define DECL_SF1(name, zt, yt) \
    VO name(zt *z, yt *y)

DECL_SF1(bfact, B, B);
DECL_SF1(ifact, I, I);
DECL_SF1(dfact, D, D);
DECL_SF1(jfact, Z, Z);

DECL_SF1(isignum, I, I);
DECL_SF1(dsignum, I, D);

#endif
