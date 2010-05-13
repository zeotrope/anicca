#ifndef _LEXER_H
#define _LEXER_H

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

#define NCOL 9
#define NROW 10

static ST dfa[NROW][NCOL] = {
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

CHARTYPE char_type(C);
A array_str(C *);
MONAD(token_index);
DYAD(tokens);

#endif
