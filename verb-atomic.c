#include <stdio.h>
#include <stdlib.h>

#include "anicca.h"
#include "error.h"
#include "memory.h"
#include "convert.h"
#include "function.h"
#include "verb-scalar2.h"
#include "verb-atomic.h"
#include "util.h"

static UC vaindx[256] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,0,0,0,0,2,3,0,4,0,0, /* !"#$%&'()*+,-./*/
    0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0, /*0123456789:;<=>?*/
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*@ABCDEFGHIJKLMNO*/
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0, /*PQRSTUVWXYZ[\]^_*/
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*`abcdefghijklmno*/
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*pqrstuvwxyz{|}~ */
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

#define NVA 7

static VA verbatm[NVA] = {
    {{ {NULL,    0      }, {NULL,    0      },  {NULL,   0      },
       {NULL,    0      }, {NULL,    0      },  {NULL,   0      }  }},

    {{ {bdivide, VAB|VRD}, {idivide, VAI|VRD}, {ddivide, VAD|VRD},
       {jdivide, VAZ|VRZ}, {ddivide, VAD|VRD}, {ddivide, VAZ|VRZ}  }},

    {{ {btimes,  VAB|VRB}, {itimes,  VAI|VRI}, {dtimes,  VAD|VRD},
       {jtimes,  VAZ+VRZ}, {dtimes,  VAD|VRD}, {dtimes,  VAZ|VRZ}  }},

    {{ {bplus,   VAB|VRI}, {iplus,   VAI|VRI}, {dplus,   VAD|VRD},
       {jplus,   VAZ|VRZ}, {dplus,   VAD|VRD}, {dplus,   VAZ|VRZ}  }},

    {{ {bminus,  VAB|VRI}, {iminus,  VAI|VRI}, {dminus,  VAD|VRD},
       {dminus,  VAD|VRD}, {dminus,  VAD|VRD}, {dminus,  VAZ|VRZ}  }},

    {{ {blthan,  VAB|VRB}, {ilthan,  VAI|VRB}, {dlthan,  VAD|VRB},
       {dlthan,  VAD|VRD}, {dlthan,  VAD|VRD}, {dlthan,  VAZ|VRZ}  }},

    {{ {bpower,  VAB|VRB}, {ipower,  VAI|VRD}, {dpower,  VAD|VRD},
       {dpower,  VAD|VRD}, {dlthan,  VAD|VRD}, {dlthan,  VAZ|VRZ}  }}
};

I atype(I cv) { R cv&VAB ? BOOL : cv&VAI ? INT : cv&VAD ? FLT : CMPX; }

I rtype(I cv) { R cv&VRB ? BOOL : cv&VRI ? INT : cv&VRD ? FLT : CMPX; }

/*
  va2: Execute dyadic atomic verb.
  input:
    id: ID of atomic verb to execute.
    x:  left argument.
    y:  right argument.
  output:
    Result of the dyadic atomic verb.
*/
A va2(C id, A x, A y) {
    I xt = AT(x), yt = AT(y), t = MAX(xt, yt), cv, at, rt;
    I i = vaindx[id], j = (t&BOOL ? 0 : t&INT ? 1 : t&FLT ? 2 : 3);
    VA2 *vd = &(&verbatm[i])->fcv[j];
    SF f2 = vd->f; A z;
    ASSERT(xt&NUMERIC&&yt&NUMERIC, ERDOM);
    cv = vd->cv; at = atype(cv); rt = rtype(cv);
    z = sex2(xt==at ? x : conv(at,x), yt==at ? y : conv(at,y), rt, f2);
    R z;
}
