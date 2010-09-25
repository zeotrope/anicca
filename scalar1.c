#include "anicca.h"
#include "scalar1.h"

SF1(bfact, B, B, 1)
DECL_SF1(ifact, I, I) { I t=*y, r=1; DO(t, r*=t--;); *z=r; }
DECL_SF1(dfact, D, D) { }
DECL_SF1(jfact, Z, Z) { }

SF1(isignum, I, I, *y < 0 ? -1 : *y > 0 ? 1 : 0)
SF1(dsignum, I, D, *y < 0 ? -1 : *y > 0 ? 1 : 0)

I iprod(A y) { R iprod2(AN(y),IAV(y)); }
I iprod2(I n, I *iv) { I z=1; DO(n, z*=*iv++); R z; }
