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

A convert(I t, A y);

#endif
