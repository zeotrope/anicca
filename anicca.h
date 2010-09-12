#ifndef _ANICCA_H
#define _ANICCA_H

#define DO(n, body) do {       \
        I i=0, _t=n;           \
        for (i=0; i<_t; i++) { \
            body;              \
        }                      \
} while(0)

#define R      return
#define RZ(a)  if (!(a)) { R 0; }

#define MONAD(name) A name(A y)
#define DYAD(name)  A name(A x, A y)

#define MONAD_PROLOG \
    I yt=AT(y), yr=AR(y), yn=AN(y), *ys=AS(y); A z

#define DYAD_PROLOG \
    I xt=AT(x), xn=AN(x), xr=AR(x), *xs=AS(x); \
    I yt=AT(y), yn=AN(y), yr=AR(y), *ys=AS(y); \
    A z /* More declarations or assignment */

#define DMONAD(name) A name(A y, A self)
#define DDYAD(name)  A name(A x, A y, A self)

#include "types.h"
#include "globals.h"
#include "char.h"
#include "error.h"
#include "memory.h"
#include "function.h"
#include "print.h"

#endif
