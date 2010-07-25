#ifndef _CHAR_H
#define _CHAR_H

#define CBANG  '!'
#define CDQOT  '"'
#define CPOND  '#'
#define CDOLR  '$'
#define CPERC  '%'
#define CAMPR  '&'
#define CLPAR  '('
#define CRPAR  ')'
#define CSTAR  '*'
#define CPLUS  '+'
#define CCOMA  ','
#define CSUBT  '-'
#define CDOT   '.'
#define CSLASH '/'
#define CCOL   ':'
#define CSCOL  ';'
#define CLT    '<'
#define CEQ    '='
#define CGT    '>'
#define CQUES  '?'
#define CAT    '@'
#define CSAMEL '['
#define CPREFX '\\'
#define CSAMER ']'
#define CIOTA  'i'
#define CTILDE '~'
#define CSQOT  '\''

typedef enum {
    CFIT = 127,
    CNOT,
    CHALF,
    CDO,
    CBASE,
    CSPRS,
    CMTRI,
    CAPSE,
    CAND,
    COR,
    CSTCH,
    CSTEP
} PUNCDOT;

typedef enum {
    CFRGN = 181,
    CFORM,
    CABSE,
    CRECR,
    CSQRT,
    CSQR,
    CDBL,
    CLAMN,
    CCAP = 127
} PUNCCOL;

#define CHOOK 200
#define CFORK 201

#endif
