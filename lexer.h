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
        CQ  /* "'"   */
} CHARTYPE;

typedef enum {
        EO, /* No effect */
        EI, /* Word start index = index */
        EN  /* Emit word start index and length, word start index = index */
} ACTION;

typedef struct _state {
        C new;
        C effect;
} ST;

#define NCOL 9
#define NROW 10

static ST dfa[NROW][NCOL] = {
        {{SX,EN},{SS,EO},{SA,EN},{SN,EN},{SA,EN},{S9,EN},{SX,EN},{SX,EN},{SQ,EN}}, /* SS  */
        {{SX,EI},{SS,EI},{SA,EI},{SN,EI},{SA,EI},{S9,EI},{SX,EO},{SX,EO},{SQ,EI}}, /* SX  */
        {{SX,EI},{SS,EI},{SA,EO},{SA,EO},{SA,EO},{SA,EO},{SX,EO},{SX,EO},{SQ,EI}}, /* SA  */
        {{SX,EI},{SS,EI},{SA,EO},{SA,EO},{SNB,0},{SA,EO},{SX,EO},{SX,EO},{SQ,EI}}, /* SN  */
        {{SX,EI},{SS,EI},{SA,EO},{SA,EO},{SA,EO},{SA,EO},{SNZ,0},{SX,EO},{SQ,EI}}, /* SNB */
        {{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SX,EO},{SX,EO},{SZ,EO}}, /* SNZ */
        {{SX,EI},{SS,EI},{S9,EO},{S9,EO},{S9,EO},{S9,EO},{S9,EO},{SX,EO},{SQ,EI}}, /* S9  */
        {{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SC,EO}}, /* SQ  */
        {{SX,EI},{SS,EI},{SA,EI},{SN,EI},{SA,EI},{S9,EI},{SX,EI},{SX,EI},{SQ,EO}}, /* SC  */
        {{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO}}  /* SZ  */
        /*  CX      CS      CA      CN      CB     C9       CD      CC      CQ  */ 
};

#endif
