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
    {{ {NULL,   0}, {NULL,   0}, {NULL,   0},
       {NULL,   0}, {NULL,   0}, {NULL,   0} }},

    {{ {bdivide, VAB|VRD}, {idivide, VAI|VRD}, {ddivide, VAD|VRD},
       {ddivide, VAD|VRD}, {ddivide, VAD|VRD}, {ddivide, VAZ|VRZ} }},

    {{ {btimes, VAB|VRB},  {itimes, VAI|VRI},  {dtimes, VAD|VRD},
       {dtimes, VAD+VRD},  {dtimes, VAD|VRD},  {dtimes, VAZ|VRZ}  }},

    {{ {bplus, VAB|VRI},   {iplus, VAI|VRI},   {dplus, VAD|VRD},
       {dplus, VAD|VRD},   {dplus, VAD|VRD},   {dplus, VAZ|VRZ}   }},

    {{ {bminus, VAB|VRI},  {iminus, VAI|VRI},  {dminus, VAD|VRD},
       {dminus, VAD|VRD},  {dminus, VAD|VRD},  {dminus, VAZ|VRZ}  }},

    {{ {blthan, VAB|VRB},  {ilthan, VAI|VRB},  {dlthan, VAD|VRB},
       {dlthan, VAD|VRD},  {dlthan, VAD|VRD},  {dlthan, VAZ|VRZ}  }},

};

I atype(I cv) { return cv&VAB ? BOOL : cv&VAI ? INT : cv&VAD ? FLT : CMPX; }

I rtype(I cv) { return cv&VRB ? BOOL : cv&VRI ? INT : cv&VRD ? FLT : CMPX; }

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
    z = sex2(xt==at ? x : convert(at, x), yt==at ? y : convert(at, y), rt, f2);
    return z;
}
