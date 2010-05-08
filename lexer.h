#ifndef _LEXER_H
#define _LEXER_H

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
     CQ,  /* "'"   */
     END = -1
} CHARTYPE;

typedef enum {
     EO, /* No effect */
     EI, /* Emit word start index and length, word start index = index */
     EN  /* Word start index = index */
} ACTION;

typedef struct _state {
     C new;
     C effect;
} ST;

#define NCOL 9
#define NROW 10

static ST dfa[NROW][NCOL] = {
/*SS*/ {{SX,EN},{SS,EO},{SA,EN},{SN,EN},{SA,EN},{S9,EN},{SX,EN},{SX,EN},{SQ,EN}},
/*SX*/ {{SX,EI},{SS,EI},{SA,EI},{SN,EI},{SA,EI},{S9,EI},{SX,EO},{SX,EO},{SQ,EI}},
/*SA*/ {{SX,EI},{SS,EI},{SA,EO},{SA,EO},{SA,EO},{SA,EO},{SX,EO},{SX,EO},{SQ,EI}},
/*SN*/ {{SX,EI},{SS,EI},{SA,EO},{SA,EO},{SNB,0},{SA,EO},{SX,EO},{SX,EO},{SQ,EI}},
/*SNB*/{{SX,EI},{SS,EI},{SA,EO},{SA,EO},{SA,EO},{SA,EO},{SNZ,0},{SX,EO},{SQ,EI}},
/*SNZ*/{{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SX,EO},{SX,EO},{SZ,EO}},
/*S9*/ {{SX,EI},{SS,EI},{S9,EO},{S9,EO},{S9,EO},{S9,EO},{S9,EO},{SX,EO},{SQ,EI}},
/*SQ*/ {{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SC,EO}},
/*SC*/ {{SX,EI},{SS,EI},{SA,EI},{SN,EI},{SA,EI},{S9,EI},{SX,EI},{SX,EI},{SQ,EO}},
/*SZ*/ {{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO}}
       /* CX      CS      CA      CN      CB     C9       CD      CC      CQ   */
};

CHARTYPE char_type(C );
A array_str(C *);
MONAD(token_index);

#endif
