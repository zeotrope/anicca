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

A parse_literal(I n, C *s);
A parse_verb(I n, C *s);
A noun_index(I n, C *s);
MONAD(token_index);
DYAD(tokens);

#endif
