#include "anicca.h"
#include "verb-scalar1.h"

SF1(isignum, I, I, *y < 0 ? -1 : *y > 0 ? 1 : 0)
SF1(dsignum, I, D, *y < 0 ? -1 : *y > 0 ? 1 : 0)
