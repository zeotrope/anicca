#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "char.h"
#include "memory.h"
#include "function.h"
#include "verb.h"
#include "adverb.h"
#include "conjunction.h"
#include "primitive.h"

#define BASE 56
#define PUNC 3

static UC verbname[PUNC][BASE] = {
    {'!',   '"',   '#',   '$',   '%',   '&',   '(',   ')',   '*',   '+',
     ',',   '-',   '.',   '/',   ':',   ';',   '<',   '=',   '>',   '?',
     '@',   'A',   'C',   'D',   'E',   'H',   'I',   'L',   'M',   'S',
     'T',   '[',   '\\',  ']',   '^',   '_',   '`',   'a',   'b',   'd',
     'e',   'f',   'i',   'j',   'o',   'p',   'q',   'r',   's',   't',
     'u',   'x',   '{',   '|',   '}',   '~'},

    {CFIT,  CDO,   CBASE, CSPRS, CMTRI, CAPSE, 0,     0,     CAND,  COR,
     CSTCH, CNOT,  CEVEN, COBLQ, COBVR, CCUT,  CFLR,  CALCL, CCEIL, CROLF,
     CAGND, CANAG, CPERM, CDRVT, CMEMI, CHYPR, CINCS, CLVLO, CMEMO, 0,
     CTYLR, 0,     CSUFX, 0,     CLOG,  0,     0,     CALFA, CBOOL, CDRVF,
     CMEMB, CFIX,  CIOTA, CCMPX, CCIRC, CPOLY, 0,     CPOLR, 0,     CTYLC,
     0,     0,     CTAKE, CREV,  CDROP, CNUB},

    {CFRGN, CFORM, CABSE, CRECR, CSQRT, CUNDR, 0,     0,     CSQR,  CDBL,
     CLAMN, CHALF, CODD,  CGRDU, CADVR, CWORD, CLTEQ, CAGBL, CGTEQ, 0,
     CATR,  0,     0,     CSECN, 0,     0,     0,     CLVLA, 0,     CSPRD,
     0,     CCAP,  CGRDD, 0,     CPOWR, 0,     CEVOK, CACE,  0,     0,
     0,     0,     CSTEP, 0,     0,     CPRIM, CPRFC, 0,     CSYMB, CWTTY,
     CUNIC, CEXT,  CTAIL, CTRAN, CCURT, CNEQ}
};


UC verb_name(I n, C *s) {
    UC d, *t;
    I i, j;

    switch (n) {
    case 1: return *s;
    case 2: {
        d = s[1];
        i = d==CDOT ? 1 : d==CCOL ? 2 : 0;
        if (i > 0) {
            t = memchr(verbname[0], *s, BASE);
            j = t - verbname[0];
            return verbname[i][j];
        }
    }
    }
    return *s;
}

static UC primindx[256] = {
/*0*/  0,  54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
/*1*/  69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 0,  0,  0,  0,  0,  0,
/*2*/  0,  1,  2,  3,  4,  5,  6,  0,  7,  8,  9,  10, 11, 12, 13, 14,
/*3*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  15, 16, 17, 18, 19, 20,
/*4*/  21, 22, 0,  23, 24, 25, 0,  0,  26, 27, 0,  0,  28, 29, 0,  0,
/*5*/  0,  0,  0,  0,  30, 0,  0,  0,  0,  0,  0,  31, 32, 33, 34, 0,
/*6*/  35, 36, 37, 0,  38, 39, 40, 0,  0,  41, 42, 0,  0,  0,  0,  43,
/*7*/  44, 45, 46, 0,  48, 49, 0,  0,  50, 0,  0,  50, 51, 52, 53, 0,
/*8*/  0,  79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93,
/*9*/  94, 95, 96, 97, 98, 99, 100,101,102,103,104,105,106,107,108,109,
/*a*/  110,111,112,113,114,115,0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/*b*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/*c*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/*d*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/*e*/  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
     /*0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f*/
};


#define NPRIM 116

static P primitives[NPRIM+1] = {
    /* 0      0   */ {0,    NULL,       NULL,    0, 0, 0, 0},
    /* 1   !  33  */ {VERB, fact,       outof,   0, 0, 0, 0},
    /* 2   "  34  */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 3   #  35  */ {VERB, tally,      copy,    0, 0, 0, 0},
    /* 4   $  36  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 5   %  37  */ {VERB, reciprocal, divide,  0, 0, 0, 0},
    /* 6   &  38  */ {CONJ, NULL,       amper,   0, 0, 0, 0},
    /* 7   (  40  */ {LPAR, NULL,       NULL,    0, 0, 0, 0},
    /* 8   )  41  */ {RPAR, NULL,       NULL,    0, 0, 0, 0},
    /* 9   *  42  */ {VERB, signum,     times,   0, 0, 0, 0},
    /* 10  +  43  */ {VERB, conjugate,  plus,    0, 0, 0, 0},
    /* 11  ,  44  */ {VERB, NULL,       append,  0, 0, 0, 0},
    /* 12  -  45  */ {VERB, negate,     minus,   0, 0, 0, 0},
    /* 13  .  46  */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 14  /  47  */ {ADV,  slash,      NULL,    0, 0, 0, 0},
    /* 15  :  58  */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 16  ;  59  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 17  <  60  */ {VERB, box,        lthan,   0, 0, 0, 0},
    /* 18  =  61  */ {VERB, NULL,       equal,   0, 0, 0, 0},
    /* 19  >  62  */ {VERB, NULL,       gthan,   0, 0, 0, 0},
    /* 20  ?  63  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 21  @  64  */ {CONJ, NULL,       atsign,  0, 0, 0, 0},
    /* 22  A. 65  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 23  C. 66  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 24  D. 68  */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 25  E. 69  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 26  H. 72  */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 27  I. 73  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 28  L. 76  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 29  M. 77  */ {ADV,  NULL,       NULL,    0, 0, 0, 0},
    /* 30  T. 84  */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 31  [  91  */ {VERB, same,       left,    0, 0, 0, 0},
    /* 32  \  92  */ {ADV,  NULL,       NULL,    0, 0, 0, 0},
    /* 33  ]  93  */ {VERB, same,       right,   0, 0, 0, 0},
    /* 34  ^  94  */ {VERB, expntl,     NULL,    0, 0, 0, 0},
    /* 35  `  96  */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 36  a. 97  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 37  b. 98  */ {ADV,  NULL,       NULL,    0, 0, 0, 0},
    /* 38  d. 100 */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 39  e. 101 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 40  f. 102 */ {ADV,  NULL,       NULL,    0, 0, 0, 0},
    /* 41  i. 105 */ {VERB, iota,       NULL,    0, 0, 0, 0},
    /* 42  j. 106 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 43  o. 111 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 44  p. 112 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 45  q. 113 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 46  r. 114 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 47  t. 116 */ {ADV,  NULL,       NULL,    0, 0, 0, 0},
    /* 48  u. 117 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 49  x. 120 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 50  {  123 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 51  |  124 */ {VERB, NULL,       residue, 0, 0, 0, 0},
    /* 52  }  125 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 53  ~  126 */ {ADV,  tilde,      NULL,    0, 0, 0, 0},
    /* 54  !. 1   */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 55  ". 2   */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 56  #. 3   */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 57  $. 4   */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 58  %. 5   */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 59  &. 6   */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 60  *. 7   */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 61  +. 8   */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 62  ,. 9   */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 63  -. 10  */ {VERB, not,        NULL,    0, 0, 0, 0},
    /* 64  .. 11  */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 65  /. 12  */ {ADV,  NULL,       NULL,    0, 0, 0, 0},
    /* 66  :. 13  */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 67  ;. 14  */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 68  <. 15  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 69  =. 16  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 70  >. 17  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 71  ?. 18  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 72  @. 19  */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 73  \. 20  */ {ADV,  NULL,       NULL,    0, 0, 0, 0},
    /* 74  ^. 21  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 75  {. 22  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 76  |. 23  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 77  }. 24  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 78  ~. 25  */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 79  !: 129 */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 80  ": 130 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 81  #: 131 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 82  $: 132 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 83  %: 133 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 84  &: 134 */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 85  *: 135 */ {VERB, square,     NULL,    0, 0, 0, 0},
    /* 86  +: 136 */ {VERB, duble,      NULL,    0, 0, 0, 0},
    /* 87  ,: 137 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 88  -: 138 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 89  .: 139 */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 90  /: 140 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 91  :: 141 */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 92  ;: 142 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 93  <: 143 */ {VERB, decrement,  NULL,    0, 0, 0, 0},
    /* 94  =: 144 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 95  >: 145 */ {VERB, increment,  NULL,    0, 0, 0, 0},
    /* 96  @: 146 */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 97  D: 147 */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 98  L: 148 */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 99  S: 149 */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 100 [: 150 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 101 \: 151 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 102 a: 152 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 103 i: 153 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 104 p: 154 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 105 q: 155 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 106 s: 156 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 107 t: 157 */ {ADV,  NULL,       NULL,    0, 0, 0, 0},
    /* 108 u: 158 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 109 x: 159 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 110 ^: 160 */ {CONJ, NULL,       cartcol, 0, 0, 0, 0},
    /* 111 `: 161 */ {CONJ, NULL,       NULL,    0, 0, 0, 0},
    /* 112 {: 162 */ {VERB, tail,       NULL,    0, 0, 0, 0},
    /* 113 |: 163 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 114 }: 164 */ {VERB, NULL,       NULL,    0, 0, 0, 0},
    /* 115 ~: 165 */ {VERB, NULL,       NULL,    0, 0, 0, 0}
};

A primitive_lookup(UC id) {
    A z;
    P *p = &primitives[primindx[id]];
    I t = p->type;

    switch (t) {
    case NOUN: break;
    case ADV:
    case VERB:
    case CONJ: return func_def(id, t, p->f1, p->f2, NULL, NULL, NULL, \
                        p->lr, p->mr, p->rr, p->inv);
    case LPAR: return lpar;
    case RPAR: return rpar;
    default:   return mark;
    }

    return mark;
}
