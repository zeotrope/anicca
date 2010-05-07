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
        SQQ, /* Even Quote       */
        SZ   /* Trailing Comment */
} STATE;

typedef enum {
        EI,
        EN
} ACTION;

typedef struct _state {
        C new;
        C effect;
} ST;

#define NROW 10
#define NCOL 9

static ST dfa[NROW][NCOL] = {
        {{SX,EN},{SS,0 },{SA,EN},{SN,EN},{SA,EN},{S9,EN},{SX,EN},{SX,EN},{SQ,EN}}, /* SS  */
        {{SX,EI},{SS,EI},{SA,EI},{SN,EI},{SA,EI},{S9,EI},{SX,0 },{SX,0 },{SQ,EI}}, /* SX  */
        {{SX,EI},{SS,EI},{SA,0 },{SA,0 },{SA,0 },{SA,0 },{SX,0 },{SX,0 },{SQ,EI}}, /* SA  */
        {{SX,EI},{SS,EI},{SA,0 },{SA,0 },{SNB,0},{SA,0 },{SX,0 },{SX,0 },{SQ,EI}}, /* SN  */
        {{SX,EI},{SS,EI},{SA,0 },{SA,0 },{SA,0 },{SA,0 },{SNZ,0},{SX,0 },{SQ,EI}}, /* SNB */
        {{SZ,0 },{SZ,0 },{SZ,0 },{SZ,0 },{SZ,0 },{SZ,0 },{SX,0 },{SX,0 },{SZ,0 }}, /* SNZ */
        {{SX,EI},{SS,EI},{S9,0 },{S9,0 },{S9,0 },{S9,0 },{S9,0 },{SX,0 },{SQ,EI}}, /* S9  */
        {{SQ,0 },{SQ,0 },{SQ,0 },{SQ,0 },{SQ,0 },{SQ,0 },{SQ,0 },{SQ,0 },{SQQ,0}}, /* SQ  */
        {{SX,EI},{SS,EI},{SA,EI},{SN,EI},{SA,EI},{S9,EI},{SX,EI},{SX,EI},{SQ,0 }}, /* SQQ */
        {{SZ,0 },{SZ,0 },{SZ,0 },{SZ,0 },{SZ,0 },{SZ,0 },{SZ,0 },{SZ,0 },{SZ,0 }}  /* SZ  */
        /*  CX      CS      CA      CN      CB     C9       CD      CC      CQ  */ 
};

#endif
