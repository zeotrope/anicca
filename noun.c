#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "anicca.h"
#include "memory.h"
#include "lexer.h"
#include "noun.h"
#include "atom.h"
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

PARSE(atom) {
    N res;
    C *se;

    se = parse_exp(n, s, &res);
    *a = res;

    return se;
}

PARSE(base) {
    C *se;
    N b;
    B good;

    se = parse_pi(n, s, a);
    if (!se) return NULL;
    n -= (se+1) - s;
    if (se[0] == 'b') {
        se = parse_pi(n, se+1, &b);
        if (!se) return NULL;
        good = abase(a, b);
    }

    return good? se : NULL;
}

PARSE(pi) {
    C *p, *x;
    N b;
    C *se;
    B good;

    se = parse_pi(n, s, a);
    if (!se) return NULL;
    n -= (se+1) - s;
    if (se[0] == 'p') {
        se = parse_pi(n, se+1, &b);
        if (!se) return NULL;
        good = apitime(a, b);
    }
    else if (se[0] == 'x') {
        se = parse_pi(n, se+1, &b);
        if (!se) return NULL;
        good = aeuler(a, b);
    }

    return good? se : NULL;
}

PARSE(cmpx) {
    C *j, *r;
    N b;
    C *se;
    B good;

    se = parse_exp(n, s, a);
    if (!se) return NULL;
    n -= se - s;
    if (s[0] == 'j') {
        se = parse_exp(n-1, se+1, &b);
        if (!se) return NULL;
        good = acmpx(a, b);
    }
    else if (s[0] == 'a') {
        if (s[1] == 'd') {
            se = parse_exp(n-2, se+2, &b);
            if (!se) return NULL;
            good = aangd(a, b);
        }
        else if (s[1] == 'r') {
            se = parse_exp(n-2, se+2, &b);
            if (!se) return NULL;
            good = aangr(a, b);
        }
    }

    return good? se : NULL;
}

PARSE(exp) {
    C *se;
    N b;
    B good;

    se = parse_num(n, s, a);
    if (!se) return NULL;
    n -= se - s;
    if (se[0] == 'e') {
        se = parse_num(n-1, se+1, &b);
        if (b.t > INT) {
            fprintf(stderr, "ill-formed number");
            return NULL;
        }
        good = aexp(a, b);
    }
    return good? se : NULL;
}

PARSE(num) {
    C *d, *e;

    d = memchr(s, '.', n);
    if (d) {
        a->val.d = strtod(s, &e);
        a->t = FLT;
    }
    else {
        a->val.i = strtol(s, &e, 10);
        a->t = INT;
    }

    return e;
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

