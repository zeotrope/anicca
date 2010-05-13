#include <stdlib.h>
#include "anicca.h"
#include "memory.h"
#include "verb.h"

MONAD(tally) {
     A z; return z;
}

MONAD(shape) {
     A z;
     I r = AR(y), *s = AS(y), *v;
     z = gen_array(INT, 1, r, NULL);
     v = (I*)AV(z);
     if (r > 1) {
          DO(r, v[i] = s[i]);
     } else {
          *v = AN(y);
     }
     return z;
}
