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
#define PARSE(name)    static C* parse_ ## name(I n, C *s, N *a)

PARSE(atom);
PARSE(base);
PARSE(pi);
PARSE(cmpx);
PARSE(exp);
PARSE(num);

A parse_noun(I n, C *s);

#endif
