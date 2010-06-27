#ifndef _TABLE_H
#define _TABLE_H

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

/* Noun Mapping */
static C nountype[256] = {
    /*0*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CS,CX,CX,CX,CX,CX,CX,
    /*1*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
    /*2*/ CS,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CA,CX, /* !"#$%&'()*+,-./*/
    /*3*/ CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CA,CX,CX,CX,CX,CX, /*0123456789:;<=>?*/
    /*4*/ CX,CX,CX,CX,CX,CA,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX, /*@ABCDEFGHIJKLMNO*/
    /*5*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CA, /*PQRSTUVWXYZ[\]^_*/
    /*6*/ CX,CA,CA,CX,CA,CA,CX,CX,CX,CX,CA,CX,CX,CX,CX,CX, /*`abcdefghijklmno*/
    /*7*/ CA,CX,CA,CX,CX,CX,CX,CX,CA,CX,CX,CX,CX,CX,CX,CX, /*pqrstuvwxyz{|}~ */
    /*8*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
    /*9*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
    /*a*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
    /*b*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
    /*c*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
    /*d*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
    /*e*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX
         /*0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f*/
};

static C chartype[256] = {
    /*0*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CS,CX,CX,CX,CX,CX,CX,
    /*1*/ CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,CX,
    /*2*/ CS,CX,CX,CX,CX,CX,CX,CQ,CX,CX,CX,CX,CX,CX,CD,CX, /* !"#$%&'()*+,-./*/
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
    CBANG = 33,
    CDQOT,
    CPOND,
    CDOLR,
    CPERC,
    CAMPR,
    CSQOT,
    CLPAR,
    CRPAR
} CHARS;

#endif
