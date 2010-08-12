#include "anicca.h"
#include "verb-scalar2.h"

SF2(bdivide,  D, B, *x / (D)*y)
SF2(idivide,  D, I, *x / (D)*y)
SF2(ddivide,  D, D, *x / *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(btimes,  B, B, *x * *y)
SF2(itimes,  I, I, *x * *y)
SF2(dtimes,  D, D, *x * *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(bplus,  I, B, *x + *y)
SF2(iplus,  I, I, *x + *y)
SF2(dplus,  D, D, *x + *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(bminus,  I, B, *x - *y)
SF2(iminus,  I, I, *x - *y)
SF2(dminus,  D, D, *x - *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(blthan,  B, B, *x < *y)
SF2(ilthan,  B, I, *x < *y)
SF2(dlthan,  B, D, *x < *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(bequal,  B, B, *x == *y)
SF2(iequal,  B, I, *x == *y)
SF2(dequal,  B, D, *x == *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(bgthan,  B, B, *x > *y)
SF2(igthan,  B, I, *x > *y)
SF2(dgthan,  B, D, *x > *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(bresidue,  B, B, *x % *y)
SF2(iresidue,  I, I, *x % *y)
SF2(dresidue,  D, D, *x + *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/
