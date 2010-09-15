#include <math.h>

#include "anicca.h"
#include "util.h"
#include "convert.h"
#include "lexer.h"
#include "parser.h"
#include "verb.h"

DYAD(link) { A z; R z; }

MONAD(box) { A z = sbox(y); R z; }

MONAD(unbox) { A z=ca(*AAV(y)); R z; }

DYAD(deal) { A z; R z; }

MONAD(indices) { A z; R z; }

MONAD(same) { A z=ca(y); R z; }

DYAD(left) { A z=ca(x); R z; }

DYAD(right) { A z=ca(y); R z; }

MONAD(iota) { MONAD_PROLOG; I n=1, *yv=IAV(y), *v;
    ASSERT(yt&INTEGER,ERDOM);
    DO(yn, n*=*yv++);
    z=ga(INT,yn,n,IAV(y)); v=IAV(z);
    DO(n, v[i]=i);
    R z;
}

MONAD(execute) { C *v; I yt=AT(y), n=AN(y)+1; A w, z;
    ASSERT(yt&CHAR, ERDOM);
    w=ra(y,yt,n);
    v=CAV(w); v[n-1]='\0';
    z=parse(tokens(w));
    R z;
}
