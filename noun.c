#include <stdlib.h>
#include <string.h>
#include "anicca.h"
#include "memory.h"
#include "lexer.h"
#include "noun.h"
#include "util.h"

B noun_bval(const N *n) {
    switch (n->t) {
    case BOOL:return n->val.b;
    case INT: return (n->val.i != 0);
        /* FIXME: floating point tolerance */
    case FLT: return (n->val.d != 0);
    case CMPX:return (n->val.z.real != 0);
    }
}
I noun_ival(const N *n) {
    switch (n->t) {
    case BOOL:return n->val.b;
    case INT: return n->val.i;
    case FLT: return (I) n->val.d;
    case CMPX:return (I) n->val.z.real;
    }
}
D noun_dval(const N *n) {
    switch (n->t) {
    case BOOL:return n->val.b;
    case INT: return n->val.i;
    case FLT: return n->val.d;
    case CMPX:return n->val.z.real;
    }
}
Z noun_zval(const N *n) {
    Z z = { 0, 0 };
    switch (n->t) {
    case BOOL:z.real = n->val.b; break;
    case INT: z.real = n->val.i; break;
    case FLT: z.real = n->val.d; break;
    case CMPX:return n->val.z;
    }
    return z;
}


ATOMFUNC(base) { }
ATOMFUNC(pitime) { }
ATOMFUNC(euler) { }
ATOMFUNC(cmpx) { }
ATOMFUNC(angr) { }
ATOMFUNC(angd) { }
ATOMFUNC(exp) { }

PARSE(atom) {
    N res;

    parse_num(n, s, &res);
    *a = res;

    return 1;
}

PARSE(base) {
    N b;

    parse_pi(n, s, a);
    if (s[0] == 'b') {
        parse_pi(n, s, &b);
        abase(a, b);
    }

    return 1;
}

PARSE(pi) {
    N b;

    parse_pi(n, s, a);
    if (s[0] == 'p') {
        parse_pi(n, s, &b);
        apitime(a, b);
    }
    else if (s[0] == 'x') {
        parse_pi(n, s, &b);
        aeuler(a, b);
    }

    return 1;
}

PARSE(cmpx) {
    N b;

    parse_exp(n, s, a);
    if (s[0] == 'j') {
        parse_exp(n, s, &b);
        acmpx(a, b);
    }
    else if (s[0] == 'a') {
        if (s[1] == 'd') {
            parse_exp(n, s, &b);
            aangd(a, b);
        }
        else if (s[1] == 'r') {
            parse_exp(n, s, &b);
            aangr(a, b);
        }
    }

    return 1;
}

PARSE(exp) {
    N b;

    parse_num(n, s, a);
    if (s[0] == 'e') {
        parse_num(n, s, &b);
        aexp(a, b);
    }
}

PARSE(num) {
    C *e;
    if (memchr(s, '.', n)) {
        a->val.d = strtod(s, &e);
        a->t = FLT;
    }
    else {
        a->val.i = strtol(s, &e, 10);
        a->t = INT;
    }

    return 1;
}

A parse_noun(I n, C *s) {
    A y, z;
    B *bv;
    I j, al, as, m, t = 0, *indx, *iv;
    D *dv;
    Z *zv;
    N *atm, *nouns;
    
    y = noun_index(n+1, s);
    indx = (I *)AV(y);
    m = *indx++;
    nouns = (N *)malloc(sizeof(N)*m);

    DO(m,
       j  = i+i;
       as = indx[j];
       al = indx[j+1];
       atm = &nouns[i];
       parse_atom(al, &s[as], atm); /* check error */
       t = MAX(t, atm->t);
    );

    z = gen_array(t, 1, m, NULL);

    switch (t) {
    case BOOL: {
        bv = (B *)AV(z);
        DO(m, bv[i] = noun_bval(&nouns[i]));
        break;
    }
    case INT: {
        iv = (I *)AV(z);
        DO(m, iv[i] = noun_ival(&nouns[i]));
        break;
    }
    case FLT: {
        dv = (D *)AV(z);
        DO(m, dv[i] = noun_dval(&nouns[i]));
        break;
    }
    case CMPX: {
        zv = (Z *)AV(z);
        DO(m, zv[i] = noun_zval(&nouns[i]));
        break;
    }
    }

    return z;
}

