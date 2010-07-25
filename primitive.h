#ifndef _PRIMITIVE_H
#define _PRIMITIVE_H

typedef struct _primitive {
    I type;
    AF1 f1;
    AF2 f2;
    I lr, mr, rr, inv;
} P;

/*-----------------------------------------------------------------------------*/

static UC primindx[256] = {
/*0*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*1*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*2*/  0, 1, 2, 3, 4, 5, 6, 0, 7, 8, 9, 10,11,12,13,14, /* !"#$%&'()*+,-./*/
/*3*/  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15,16,17,18,19,20, /*0123456789:;<=>?*/
/*4*/  21,22,0, 23,24,25,0, 0, 26,27,0, 0, 28,29,0, 0,  /*@ABCDEFGHIJKLMNO*/
/*5*/  0, 0, 0, 30,31,0, 0, 0, 0, 0, 0, 32,33,34,35,0,  /*PQRSTUVWXYZ[\]^_*/
/*6*/  36,37,38,0, 39,40,41,0, 0, 42,43,0, 0, 0, 0, 44, /*`abcdefghijklmno*/
/*7*/  45,46,47,48,49,50,0, 0, 51,0, 0, 52,53,54,55,56,  /*pqrstuvwxyz{|}~ */
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

#define BASE 56
#define PUNC 3

static UC verbname[PUNC][BASE] = {
{'!',   '"',   '#',   '$',   '%',   '&', '(',   ')',  '*',  '+',  ',',   '-',
 '.',   '/',   ':',   ';',   '<',   '=', '>',   '?',  '@',  'A',  'C',   'D',
 'E',   'H',   'I',   'L',   'M',   'S', 'T',   '[',  '\\', ']',  '^',   '_',
 '`',   'a',   'b',   'd',   'e',   'f', 'i',   'j',  'o',  'p',  'q',   'r',
 's',   't',   'u',   'x',   '{',   '|', '}',   '~'},

{CFIT,  CDO,   CBASE, CSPRS, CMTRI, 1,   1,     1,    CAND, COR,  CSTCH, CNOT,
 1,     1,     1,     1,     1,     1,   1,     1,    1,    1,    1,     1,
 1,     1,     1,     1,     1,     1,   1,     1,    1,    1,    1,     1,
 1,     1,     1,     1,     1,     1,   CIOTA, 1,    1,    1,    1,     1,
 1,     1,     1,     1,     1,     1,   1,     1},

{CFRGN, CFORM, CABSE, CRECR, CSQRT, 1,   1,     1,    CSQR, CDBL, CLAMN, CHALF,
 1,     1,     1,     1,     1,     1,   1,     1,    1,    1,    1,     1,
 1,     1,     1,     1,     1,     1,   1,     CCAP, 1,    1,    1,     1,
 1,     1,     1,     1,     1,     1,   1,     1,    1,    1,    1,     1,
 1,     1,     1,     1,     1,     1,   1,     1}
};

/*-----------------------------------------------------------------------------*/

#define NPRIM 57

static P primitives[NPRIM+1] = {
    /* 0     0  */ {0,    NULL,       NULL,   0, 0, 0, 0},
    /* 1  !  33 */ {VERB, fact,       outof,  0, 0, 0, 0},
    /* 2  "  34 */ {CONJ, NULL,       NULL,   0, 0, 0, 0},
    /* 3  #  35 */ {VERB, tally,      copy,   0, 0, 0, 0},
    /* 4  $  36 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 5  %  37 */ {VERB, reciprocal, divide, 0, 0, 0, 0},
    /* 6  &  38 */ {CONJ, NULL,       amper,  0, 0, 0, 0},
    /* 7  (  40 */ {LPAR, NULL,       NULL,   0, 0, 0, 0},
    /* 8  )  41 */ {RPAR, NULL,       NULL,   0, 0, 0, 0},
    /* 9  *  42 */ {VERB, signum,     times,  0, 0, 0, 0},
    /* 10 +  43 */ {VERB, conjugate,  plus,   0, 0, 0, 0},
    /* 11 ,  44 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 12 -  45 */ {VERB, negate,     minus,  0, 0, 0, 0},
    /* 13 .  46 */ {CONJ, NULL,       NULL,   0, 0, 0, 0},
    /* 14 /  47 */ {ADV,  slash,      NULL,   0, 0, 0, 0},
    /* 15 :  58 */ {CONJ, NULL,       NULL,   0, 0, 0, 0},
    /* 16 ;  59 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 17 <  60 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 18 =  61 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 19 >  62 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 20 ?  63 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 21 @  64 */ {CONJ, NULL,       at,     0, 0, 0, 0},
    /* 22 A. 59 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 23 C. 60 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 24 D. 61 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 25 E. 62 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 26 H. 63 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 27 I. 59 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 28 L. 60 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 29 M. 61 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 30 S. 62 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 31 T. 63 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 32 [  59 */ {VERB, same,       left,   0, 0, 0, 0},
    /* 33 \  60 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 34 ]  61 */ {VERB, same,       right,  0, 0, 0, 0},
    /* 35 ^  62 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 36 `  59 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 37 a. 60 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 38 b. 61 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 39 d. 62 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 40 e. 63 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 41 f. 59 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 42 i. 60 */ {VERB, iota,       NULL,   0, 0, 0, 0},
    /* 43 j. 61 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 44 o. 62 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 45 p. 63 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 46 q. 64 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 47 r. 65 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 48 s. 66 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 49 t. 67 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 50 u. 68 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 51 x. 71 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 52 {  59 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 53 |  59 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 54 }  59 */ {VERB, NULL,       NULL,   0, 0, 0, 0},
    /* 55 ~  59 */ {ADV,  tilde,      NULL,   0, 0, 0, 0},
    /* 56 [: 56 */ {VERB, NULL,       NULL,   0, 0, 0, 0} /*not proper position*/
};

/*-----------------------------------------------------------------------------*/

C verb_name(I n, C *s);
A primitive_lookup(UC c);

#endif
