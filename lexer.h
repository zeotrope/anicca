#ifndef _LEXER_H
#define _LEXER_H

#define GENPRIM(type)  A gen_ ## type(A y, C *s)
#define GENERATE(type) A gen_ ## type(I n, C *s)

typedef enum {
     SS,  /* Space            */
     SX,  /* Unknown          */
     SA,  /* Alphanumeric     */
     SN,  /* N                */
     SNB, /* NB               */
     SNZ, /* NB.              */
     S9,  /* Number           */
     SQ,  /* Quote            */
     SC,  /* Even Quote       */
     SZ   /* Trailing Comment */
} STATE;

typedef enum {
     CX, /* Other */
     CS, /* Space */
     CA, /* Alpha */
     CN, /* "N"   */
     CB, /* "B"   */
     C9, /* Num   */
     CD, /* "."   */
     CC, /* ":"   */
     CQ, /* "'"   */
     END = -1
} CHARTYPE;

static C chartype[256] = {
/*0*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CS,CX,CX,CX,CX,CX,CX,
/*1*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
/*2*/ CS,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CD,CX, /* !"#$%&'()*+,-./*/
/*3*/ C9,C9,C9,C9,C9,C9,C9,C9,C9,C9,CC,CX,CX,CX,CX,CX, /*0123456789:;<=>?*/
/*4*/ CX,CA,CB,CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CN,CA, /*@ABCDEFGHIJKLMNO*/
/*5*/ CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CX,CX,CX,CX,C9, /*PQRSTUVWXYZ[\]^_*/
/*6*/ CX,CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CA, /*`abcdefghijklmno*/
/*7*/ CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CX,CX,CX,CX,CX, /*pqrstuvwxyz{|}~ */
/*8*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
/*9*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
/*a*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
/*b*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
/*c*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
/*d*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
/*e*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX
     /*0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f*/
};

typedef enum {
     EO,  /* No effect */
     EN,  /* Word start index = index,   j =. i  */
     EW,  /* emitword(i,j,state,char)),  j =. i  */
     EWR, /* emitword(i,j,state,char)),  j =. _1 */
     EV,  /* emitvector(i,j,state,char), j =. i  */
     EVR, /* emitvector(i,j,state,char), j =. _1 */
     ES   /* Stop */
} ACTION;

typedef struct _state {
     C new;
     C effect;
} ST;

#define NCOL 2
#define NROW 2

static ST noun[NROW][NCOL] = {
/* SS */ {{SS, EO},{SX, EN}},
/* SX */ {{SS, EW},{SX, EO}}
         /*  CS       CX  */
};

#define DCOL 9
#define DROW 10

static ST dfa[DROW][DCOL] = {
/*SS*/ {{SX,EN},{SS,EO} ,{SA,EN},{SN,EN},{SA,EN} ,{S9,EN},{SX,EN} ,{SX,EN},{SQ,EN}},
/*SX*/ {{SX,EW},{SS,EWR},{SA,EW},{SN,EW},{SA,EW} ,{S9,EW},{SX,EO} ,{SX,EO},{SQ,EW}},
/*SA*/ {{SX,EW},{SS,EWR},{SA,EO},{SA,EO},{SA,EO} ,{SA,EO},{SX,EO} ,{SX,EO},{SQ,EW}},
/*SN*/ {{SX,EW},{SS,EWR},{SA,EO},{SA,EO},{SNB,EO},{SA,EO},{SX,EO} ,{SX,EO},{SQ,EW}},
/*SNB*/{{SX,EW},{SS,EWR},{SA,EO},{SA,EO},{SA,EO} ,{SA,EO},{SNZ,EO},{SX,EO},{SQ,EW}},
/*SNZ*/{{SZ,EO},{SZ,EO} ,{SZ,EO},{SZ,EO},{SZ,EO} ,{SZ,EO},{SX,EO} ,{SX,EO},{SZ,EO}},
/*S9*/ {{SX,EV},{SS,EVR},{S9,EO},{S9,EO},{S9,EO} ,{S9,EO},{S9,EO} ,{SX,EO},{SQ,EV}},
/*SQ*/ {{SQ,EO},{SQ,EO} ,{SQ,EO},{SQ,EO},{SQ,EO} ,{SQ,EO},{SQ,EO} ,{SQ,EO},{SC,EO}},
/*SC*/ {{SX,EW},{SS,EWR},{SA,EW},{SN,EW},{SA,EW} ,{S9,EW},{SX,EW} ,{SX,EW},{SQ,EO}},
/*SZ*/ {{SZ,EO},{SZ,EO} ,{SZ,EO},{SZ,EO},{SZ,EO} ,{SZ,EO},{SZ,EO} ,{SZ,EO},{SZ,EO}}
       /* CX      CS       CA      CN      CB       C9      CD       CC      CQ   */
};

A array_str(C *);
A noun_start(I, C *);
A noun_start2(I, C *);

GENPRIM(bool);
GENPRIM(int);
GENERATE(num);
GENERATE(char);

MONAD(token_index);
DYAD(tokens);

#endif
