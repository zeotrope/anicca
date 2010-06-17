#include <stdlib.h>
#include <string.h>
#include "anicca.h"
#include "memory.h"
#include "lexer.h"
#include "noun.h"
#include "util.h"

ATOMFUNC(base) {
    return 1;
}

ATOMFUNC(pitime) {
    return 1;
}

ATOMFUNC(euler) {
    return 1;
}

ATOMFUNC(cmpx) {
    return 1;
}

ATOMFUNC(angr) {
    return 1;
}

ATOMFUNC(angd) {
    return 1;
}

ATOMFUNC(exp) {
    return 1;
}

PARSE(atom) {
    N res;

    parse_base(n, s, &res);
    *a = res;

    return 1;
}

PARSE(base) {
    C *c;
    N b;

    c = memchr(s, 'b', n);
    parse_pi(c?c-s:n, s, a);

    if (c) {
        c++;
        parse_pi(n+s-c, c, &b);
        abase(a, b);
    }

    return 1;
}

PARSE(pi) {
    C *p, *x;
    N b;

    p = memchr(s, 'p', n);
    x = memchr(s, 'x', n);
    parse_cmpx(p?p-s:x?x-s:n, s, a);

    if (p) {
        p++;
        parse_cmpx(n+s-p, p, &b);
        apitime(a, b);
    }
    else if (x) {
        x++;
        parse_cmpx(n+s-x, x, &b);
        aeuler(a, b);
    }

    return 1;
}

PARSE(cmpx) {
    C *j, *r;
    N b;

    j = memchr(s, 'j', n);
    r = memchr(s, 'a', n);
    parse_exp(j?j-s:r?r-s:n, s, a);

    if (j) {
        j++;
        parse_exp(n+s-j, j, &b);
        acmpx(a, b);
    }
    else if (r) {
        if (*r == 'd') {
            r++;
            parse_exp(n+s-r, r, &b);
            aangd(a, b);
        }
        else if (*r == 'r') {
            r++;
            parse_exp(n+s-r, r, &b);
            aangr(a, b);
        }
    }

    return 1;
}

PARSE(exp) {
    C *e;
    N b;

    e = memchr(s, 'e', n);
    if (!e) { e = memchr(s, 'E', n); }
    parse_num(e?e-s:n, s, a);

    if (e) {
        e++;
        parse_num(n+s-e, e, &b);
        aexp(a, b);
    }

    return 1;
}

PARSE(num) {
    C *d, *e;

    d = memchr(s, '.', n);
    if (d) {
        a->val.d = strtod(s, &e);
    }
    else {
        a->val.i = strtol(s, &e, 10);
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
        DO(m, bv[i] = nouns[i].val.b);
        break;
    }
    case INT: {
        iv = (I *)AV(z);
        DO(m, iv[i] = nouns[i].val.i);
        break;
    }
    case FLT: {
        dv = (D *)AV(z);
        DO(m, dv[i] = nouns[i].val.d);
        break;
    }
    case CMPX: {
        zv = (Z *)AV(z);
        DO(m, zv[i] = nouns[i].val.z);
        break;
    }
    }

    return z;
}

