#include "anicca.h"
#include "verb-scalar2.h"

SF2(bdivide,  I, I, *x / *y)
SF2(bdivide2, I, B, *x / *y)
SF2(idivide,  D, I, *x / *y)
SF2(ddivide,  D, D, *x / *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(btimes,  I, I, *x * *y)
SF2(btimes2, I, B, *x * *y)
SF2(itimes,  D, I, *x * *y)
SF2(dtimes,  D, D, *x * *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(bplus,  I, I, *x + *y)
SF2(bplus2, I, B, *x + *y)
SF2(iplus,  D, I, *x + *y)
SF2(dplus,  D, D, *x + *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(bminus,  I, I, *x - *y)
SF2(bminus2, I, B, *x - *y)
SF2(iminus,  D, I, *x - *y)
SF2(dminus,  D, D, *x - *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(blthan,  I, I, *x < *y)
SF2(blthan2, I, B, *x < *y)
SF2(ilthan,  D, I, *x < *y)
SF2(dlthan,  D, D, *x < *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(bequal,  I, I, *x == *y)
SF2(bequal2, I, B, *x == *y)
SF2(iequal,  D, I, *x == *y)
SF2(dequal,  D, D, *x == *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(bgthan,  I, I, *x > *y)
SF2(bgthan2, I, B, *x > *y)
SF2(igthan,  D, I, *x > *y)
SF2(dgthan,  D, D, *x > *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/

SF2(bresidue,  I, I, *x % *y)
SF2(bresidue2, I, B, *x % *y)
SF2(iresidue,  D, I, *x % *y)
SF2(dresidue,  D, D, *x + *y)
/*SF2(jplus,  Z, Z, zplus(x,y))*/
