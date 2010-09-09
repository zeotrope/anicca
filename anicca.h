#ifndef _ANICCA_H
#define _ANICCA_H

#define DO(n, body) do {       \
        I i=0, _t=n;           \
        for (i=0; i<_t; i++) { \
            body;              \
        }                      \
} while(0)

#define R      return
#define RZ(a)  if (!(a)) { return 0; }

#include "types.h"
#include "globals.h"

#define MONAD(name) A name(A y)
#define DYAD(name)  A name(A x, A y)

#define DMONAD(name) A name(A y, A self)
#define DDYAD(name)  A name(A x, A y, A self)

#endif
