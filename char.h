#ifndef _CHAR_H
#define _CHAR_H

#define CBANG  '!'
#define CDQOT  '"'
#define CPOND  '#'
#define CDOLR  '$'
#define CPERC  '%'
#define CAMPR  '&'
#define CSQOT  '\''
#define CLPAR  '('
#define CRPAR  ')'
#define CSTAR  '*'
#define CPLUS  '+'
#define CCOMA  ','
#define CSUBT  '-'
#define CDOT   '.'
#define CFWSL  '/'
#define CCOL   ':'
#define CSCOL  ';'
#define CLT    '<'
#define CEQ    '='
#define CGT    '>'
#define CQUES  '?'
#define CAT    '@'
#define CSAMEL '['
#define CBKSL  '\\'
#define CSAMER ']'
#define CPOW   '^'
#define CUNDS  '_'
#define CBTIK  '`'
#define CFROM  '{'
#define CMOD   '|'
#define CAMND  '}'
#define CTILDE '~'

#define CANAG 'A'
#define CPERM 'C'
#define CDRVT 'D'
#define CMEMI 'E'
#define CHYPR 'H'
#define CINCS 'I'
#define CLVLO 'L'
#define CMEMO 'M'
#define CTYLR 'T'

#define CALFA 'a'
#define CBOOL 'b'
#define CDRVF 'd'
#define CMEMB 'e'
#define CFIX  'f'
#define CIOTA 'i'
#define CCMPX 'j'
#define CCIRC 'o'
#define CPOLY 'p'
#define CPOLR 'r'
#define CTYLC 't'

#define CZERO '0'
#define CONE  '1'

typedef enum {
    CFIT = 1,
    CDO,
    CBASE,
    CSPRS,
    CMTRI,
    CAPSE,
    CAND,
    COR,
    CSTCH,
    CNOT,
    CEVEN,
    COBLQ,
    COBVR,
    CCUT,
    CFLR,
    CALCL,
    CCEIL,
    CROLF,
    CAGND,
    CSUFX,
    CLOG,
    CTAKE,
    CREV,
    CDROP,
    CNUB
} PUNCDOT;

typedef enum {
    CFRGN = 129,
    CFORM,
    CABSE,
    CRECR,
    CSQRT,
    CUNDR,
    CSQR,
    CDBL,
    CLAMN,
    CHALF,
    CODD,
    CGRDU,
    CADVR,
    CWORD,
    CLTEQ,
    CAGBL,
    CGTEQ,
    CATR,
    CSECN,
    CLVLA,
    CSPRD,
    CCAP,
    CGRDD,
    CACE,
    CSTEP,
    CPRIM,
    CPRFC,
    CSYMB,
    CWTTY,
    CUNIC,
    CEXT,
    CPOWR,
    CEVOK,
    CTAIL,
    CTRAN,
    CCURT,
    CNEQ
} PUNCCOL;

#define CHOOK 254
#define CFORK 255

#endif
