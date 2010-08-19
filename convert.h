#ifndef _CONVERT_H

/*
  Conversion vector:
  lowest 8 bits: argument type.
  highest 8 bits: result type.
  ItD: 0 0 0 0 1 0 0 0 | 0 0 0 0 0 1 0 0
       FLT               INT
*/

#define CNVCASE(a,b) ((a)+(VERB*(b)))
#define BtI CNVCASE(BOOL, INT)
#define BtD CNVCASE(BOOL, FLT)
#define BtZ CNVCASE(BOOL, CMPX)
#define ItD CNVCASE(INT, FLT)
#define ItZ CNVCASE(INT, CMPX)
#define DtZ CNVCASE(FLT, CMPX)

/*
  Atomic conversions
   c(Argument)T(Result)
     input:
       n: number of elements.
       v1: result.
       v2: argument.
     output: error code.
*/
B cbTi(I n, I *iv, B *bv);
B cbTd(I n, D *dv, B *bv);
B cbTz(I n, Z *zv, B *bv);
B ciTd(I n, D *dv, I *iv);
B ciTz(I n, Z *zv, I *iv);
B cdTz(I n, Z *zv, D *dv);

B aconv(I cv, I n, VP z, VP y);
A conv(I t, A y);

#endif
