#ifndef _NOUN_H
#define _NOUN_H

typedef struct _noun {
    I t;
    union val {
        C b;
        I i;
        D d;
        Z z;
    } val;
} N;

B noun_bval(const N *n);
I noun_ival(const N *n);
D noun_dval(const N *n);
Z noun_zval(const N *n);

#define ATOMFUNC(name) static N a ## name(N *a, N b)

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

ATOMFUNC(base);
ATOMFUNC(pitime);
ATOMFUNC(euler);
ATOMFUNC(cmpx);
ATOMFUNC(ngr);
ATOMFUNC(ngd);
ATOMFUNC(exp);

PARSE(atom);
PARSE(base);
PARSE(pi);
PARSE(cmpx);
PARSE(exp);
PARSE(num);

A parse_noun(I n, C *s);

#endif
