#ifndef _NOUN_H
#define _NOUN_H

typedef struct _noun {
    I t;
    union val {
        B b;
        I i;
        D d;
        Z z;
    } val;
} N;

#define NT(n) (n->t)
#define NV(n) (n->val)
#define NB(n) (NV(n).b)
#define NI(n) (NV(n).i)
#define ND(n) (NV(n).d)
#define NZ(n) (NV(n).z)

#define NVAL(name, t) t noun_ ## name(const N *a)

NVAL(bval, B);
NVAL(ival, I);
NVAL(dval, D);
NVAL(zval, Z);

/*
  parse_*() functions
  input:
   n: length of string
   s: string
  output:
   a: noun result of parsing
   returns pointer to character after last used in parsing,
   or NULL if parsing fails.
*/
#define PARSE(name) static C* parse_ ## name(I n, C *s, N *a)

PARSE(atom);
PARSE(base);
PARSE(pi);
PARSE(cmpx);
PARSE(exp);
PARSE(num);

A parse_noun(I n, C *s);
A noun_index(I n, C *s);

#endif
