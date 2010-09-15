#ifndef _VERB_H
#define _VERB_H

#include "verb-scalar.h"
#include "verb-struct.h"

MONAD(box);
MONAD(unbox);
MONAD(same);
DYAD(left);
DYAD(right);
MONAD(iota);
MONAD(execute);

I prod(I n, I *iv);

#endif
