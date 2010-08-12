#include <stdio.h>
#include <stdlib.h>

#include "anicca.h"
#include "error.h"
#include "memory.h"
#include "function.h"
#include "verb-scalar2.h"
#include "verb-atomic.h"
#include "util.h"

static UC vaindx[256] = {
    /*0*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /*1*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /*2*/ 0,0,0,0,0,1,0,0,0,0,2,3,0,4,0,0, /* !"#$%&'()*+,-./*/
    /*3*/ 0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0, /*0123456789:;<=>?*/
    /*4*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*@ABCDEFGHIJKLMNO*/
    /*5*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*PQRSTUVWXYZ[\]^_*/
    /*6*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*`abcdefghijklmno*/
    /*7*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /*pqrstuvwxyz{|}~ */
    /*8*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /*9*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /*a*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /*b*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /*c*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /*d*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /*e*/ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
         /*0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f*/
};

#define NVA 6

static VA verbatm[NVA] = {
    {{ {NULL,   0      }, {NULL,   0      }, {NULL,   0      },
       {NULL,   0      }, {NULL,   0      }, {NULL,   0      } }},

    {{ {bdivide,  VAB+VRB}, {bdivide2, VAI+VRB}, {idivide,  VAI+VRI},
       {ddivide,  VAD+VRD}, {ddivide,  VAD+VRD}, {ddivide,  VAZ+VRZ} }},

    {{ {btimes,  VAB+VRB}, {btimes2, VAI+VRB}, {itimes,  VAI+VRI},
       {dtimes,  VAD+VRD}, {dtimes,  VAD+VRD}, {dtimes,  VAZ+VRZ} }},

    {{ {bplus,  VAB+VRB}, {bplus2, VAI+VRB}, {iplus,  VAI+VRI},
       {dplus,  VAD+VRD}, {dplus,  VAD+VRD}, {dplus,  VAZ+VRZ} }},

    {{ {bminus,  VAB+VRB}, {bminus2, VAI+VRB}, {iminus,  VAI+VRI},
       {dminus,  VAD+VRD}, {dminus,  VAD+VRD}, {dminus,  VAZ+VRZ} }},

    {{ {blthan,  VAB+VRB}, {blthan2, VAI+VRB}, {ilthan,  VAI+VRI},
       {dlthan,  VAD+VRD}, {dlthan,  VAD+VRD}, {dlthan,  VAZ+VRZ} }},

};

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
    I xt = AT(x), yt = AT(y), t = MAX(xt, yt), cv;
    I i = vaindx[id], j = (t&INT ? 0 : t&BOOL ? 1 : t&FLT ? 3 : 2);
    VA2 *vd = &(&verbatm[i])->fcv[j];
    SF f2 = vd->f; A z;
    ASSERT(xt&NUMERIC&&yt&NUMERIC, ERDOM);
    z = sex2(x, y, t, f2);
    cv = vd->cv;
    return z;
}
