#ifndef _LEXER_H
#define _LEXER_H

typedef enum {
    SS, /* Space            */
    SX, /* Unknown          */
    SA, /* Alphanumeric     */
    SN, /* N                */
    SM, /* NB               */
    SO, /* NB.              */
    S9, /* Number           */
    SQ, /* Quote            */
    SC, /* Even Quote       */
    SZ  /* Trailing Comment */
} STATE;

typedef enum {
    EO, /* No effect */
    EN, /* Word start index = index,   j =. i  */
    EW, /* emitword(i,j,state,char)),  j =. i  */
    EY, /* emitword(i,j,state,char)),  j =. _1 */
    EV, /* emitvector(i,j,state,char), j =. i  */
    EZ, /* emitvector(i,j,state,char), j =. _1 */
    ES  /* Stop */
} ACTION;

typedef struct _state {
    C new;
    C effect;
} ST;

/* Noun Lexer------------------------------------------------------------------*/

#define NCOL 3
#define NROW 5

/* Noun Transition Table */
static ST noun[NROW][NCOL] = {
    /*SS*/ {{SM,ES},{SS,EO},{SX,EN}},
    /*SX*/ {{SM,EW},{SN,EW},{SA,EO}},
    /*SA*/ {{SM,EW},{SN,EW},{SA,EO}},
    /*SN*/ {{SM,ES},{SS,EO},{SX,EN}},
    /*SM*/ {{SS,ES},{SS,ES},{SS,ES}}
           /*  CX      CS      CA  */
};

/* General Lexer---------------------------------------------------------------*/

#define DCOL 9
#define DROW 10

static ST dfa[DROW][DCOL] = {
/*SS*/ {{SX,EN},{SS,EO},{SA,EN},{SN,EN},{SA,EN},{S9,EN},{SX,EN},{SX,EN},{SQ,EN}},
/*SX*/ {{SX,EW},{SS,EY},{SA,EW},{SN,EW},{SA,EW},{S9,EW},{SX,EO},{SX,EO},{SQ,EW}},
/*SA*/ {{SX,EW},{SS,EY},{SA,EO},{SA,EO},{SA,EO},{SA,EO},{SX,EO},{SX,EO},{SQ,EW}},
/*SN*/ {{SX,EW},{SS,EY},{SA,EO},{SA,EO},{SM,EO},{SA,EO},{SX,EO},{SX,EO},{SQ,EW}},
/*SM*/ {{SX,EW},{SS,EY},{SA,EO},{SA,EO},{SA,EO},{SA,EO},{SO,EO},{SX,EO},{SQ,EW}},
/*SO*/ {{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SX,EO},{SX,EO},{SZ,EO}},
/*S9*/ {{SX,EV},{SS,EZ},{S9,EO},{S9,EO},{S9,EO},{S9,EO},{S9,EO},{SX,EO},{SQ,EV}},
/*SQ*/ {{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SC,EO}},
/*SC*/ {{SX,EW},{SS,EY},{SA,EW},{SN,EW},{SA,EW},{S9,EW},{SX,EW},{SX,EW},{SQ,EO}},
/*SZ*/ {{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO}}
       /* CX      CS      CA      CN      CB      C9      CD      CC      CQ   */
};

/*-----------------------------------------------------------------------------*/

A parse_literal(I n, C *s);
A parse_verb(I n, C *s);

A noun_index(I n, C *s);
MONAD(token_index);
DYAD(tokens);

#endif
