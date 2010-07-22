#ifndef _PRIMITIVE_H
#define _PRIMITIVE_H

typedef struct _primitive {
    I type;
    AF1 f1;
    AF2 f2;
    I lr, mr, rr, inv;
} P;

/*-----------------------------------------------------------------------------*/

static C primindx[256] = {
/*0*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*1*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*2*/  0, 1, 2, 3, 4, 5, 6, 0, 7, 8, 9, 10,11,12,13,14, /* !"#$%&'()*+,-./*/
/*3*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15,16,17,18,19,20, /*0123456789:;<=>?*/
/*4*/  21,22,0, 23,24,25,0, 0, 26,27,0, 0, 28,29,0, 0,  /*@ABCDEFGHIJKLMNO*/
/*5*/  0, 0, 0, 30,31,0, 0, 0, 0, 0, 0, 32,33,34,35,0,  /*PQRSTUVWXYZ[\]^_*/
/*6*/  36,37,38,0, 39,40,41,0, 0, 0, 42,0, 0, 0, 0, 43, /*`abcdefghijklmno*/
/*7*/  44,45,46,47,48,0, 0, 49,0, 0, 0, 50,51,52,53,0,  /*pqrstuvwxyz{|}~ */
/*8*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*9*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*a*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*b*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*c*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*d*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*e*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    /* 0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f*/
};

/*-----------------------------------------------------------------------------*/

#define NPRIM 14

static P primitives[NPRIM+1] = {
    /* 0     0  */ {0,    NULL,   NULL,  0, 0, 0, 0},
    /* 1  !  33 */ {VERB, fact,   outof, 0, 0, 0, 0},
    /* 2  "  34 */ {CONJ, NULL,   NULL,  0, 0, 0, 0},
    /* 3  #  35 */ {VERB, NULL,   NULL,  0, 0, 0, 0},
    /* 4  $  36 */ {VERB, NULL,   NULL,  0, 0, 0, 0},
    /* 5  %  37 */ {VERB, NULL,   NULL,  0, 0, 0, 0},
    /* 6  &  38 */ {CONJ, NULL,   NULL,  0, 0, 0, 0},
    /* 7  (  40 */ {LPAR, NULL,   NULL,  0, 0, 0, 0},
    /* 8  )  41 */ {RPAR, NULL,   NULL,  0, 0, 0, 0},
    /* 9  *  42 */ {VERB, NULL,   NULL,  0, 0, 0, 0},
    /* 10 +  43 */ {VERB, NULL,   NULL,  0, 0, 0, 0},
    /* 11 ,  44 */ {VERB, NULL,   NULL,  0, 0, 0, 0},
    /* 12 -  45 */ {VERB, negate, minus, 0, 0, 0, 0},
    /* 13 .  46 */ {CONJ, NULL,   NULL,  0, 0, 0, 0},
    /* 14 /  47 */ {ADV,  slash,  NULL,  0, 0, 0, 0}
};

/*-----------------------------------------------------------------------------*/

#define PUNC 3

static C verbname[PUNC][NPRIM] = {
    {'!',   '"',   '#',   '$',   '%',   '&', '(', ')', '*',  '+',  ',',   '-',
     '.',   '/'},

    {CFIT,  CDO,   CBASE, CSPRS, CMTRI, 1,   1,   1,   CAND, COR,  CSTCH, CNOT,
     1,     1},

    {CFRGN, CFORM, CABSE, CRECR, CSQRT, 1,   1,   1,   CSQR, CDBL, CLAMN, CHALF,
     1,     1}
};

/*-----------------------------------------------------------------------------*/

C verb_name(I n, C *s);
A primitive_lookup(C c);

#endif
