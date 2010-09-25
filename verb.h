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
MONAD(prod);
MONAD(min);
MONAD(max);

#endif
