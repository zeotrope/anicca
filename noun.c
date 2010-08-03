#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "error.h"
#include "memory.h"
#include "memory.h"
#include "noun.h"
#include "atom.h"
#include "util.h"

NVAL(bval, B) {
    NUMERIC_SWITCH(NT(a),
        return NB(a),
        return (B)(NI(a) != 0),
        /* FIXME: floating point tolerance */
        return (B)(ND(a) != 0),
        return (B)(NZ(a).real != 0)
    );
    return 1;
}

NVAL(ival, I) {
    NUMERIC_SWITCH(NT(a),
        return (I)NB(a),
        return NI(a),
        return (I)ND(a),
        return (I)NZ(a).real
    );
    return 1;
}

NVAL(dval, D) {
    NUMERIC_SWITCH(NT(a),
        return (D)NB(a),
        return (D)NI(a),
        return ND(a),
        return NZ(a).real
    );
    return 1;
}

NVAL(zval, Z) {
    Z z = {0, 0};
    NUMERIC_SWITCH(NT(a),
        z.real = (D)NB(a); break,
        z.real = (D)NI(a); break,
        z.real = ND(a);    break,
        return NZ(a)
    );
    return z;
}

PARSE(atom) {
    N res; C *se;
    se = parse_exp(n, s, &res);
    *a = res;
    return se;
}

PARSE(base) {
    C *se; N b; B good = 1;

    se = parse_pi(n, s, a);
    if (!se) return NULL;
    n -= (se+1) - s;

    if (se[0]=='b') {
        se = parse_pi(n, se+1, &b);
        if (!se) return NULL;
        good = abase(a, b);
    }
    return good ? se : NULL;
}

PARSE(pi) {
    C *p, *x, *se; N b; B good = 1;

    se = parse_cmpx(n, s, a);
    if (!se) return NULL;
    n -= (se+1) - s;

    if (se[0]=='p') {
        se = parse_cmpx(n, se+1, &b);
        if (!se) return NULL;
        good = apitime(a, b);
    }
    else if (se[0]=='x') {
        se = parse_cmpx(n, se+1, &b);
        if (!se) return NULL;
        good = aeuler(a, b);
    }
    return good ? se : NULL;
}

PARSE(cmpx) {
    C *j, *r, *se; N b; B good = 1;

    se = parse_exp(n, s, a);
    if (!se) return NULL;
    n -= se - s;

    if (s[0]=='j') {
        se = parse_exp(n-1, se+1, &b);
        if (!se) return NULL;
        good = acmpx(a, b);
    }
    else if (s[0]=='a') {
        if (s[1]=='d') {
            se = parse_exp(n-2, se+2, &b);
            if (!se) return NULL;
            good = aangd(a, b);
        }
        else if (s[1]=='r') {
            se = parse_exp(n-2, se+2, &b);
            if (!se) return NULL;
            good = aangr(a, b);
        }
    }
    return good ? se : NULL;
}

PARSE(exp) {
    C *se; N b; B good = 1;

    se = parse_num(n, s, a);
    if (!se) return NULL;
    n -= se - s;

    if (se[0]=='e') {
        se = parse_num(n-1, se+1, &b);
        if (b.t>INT) {
            a_signal(ERLEXER);
            return NULL;
        }
        good = aexp(a, b);
    }
    return good ? se : NULL;
}

PARSE(num) {
    C *d = memchr(s, '.', n), *e;
    if (d) { ND(a) = strtod(s, &e);     NT(a) = FLT; }
    else   { NI(a) = strtol(s, &e, 10); NT(a) = INT; }
    return e;
}

/*
  parse_numeric
  input: Length of numeric string, Pointer to string.
  output: Numeric array.
*/
A parse_noun(I n, C *s) {
    A y = noun_index(n+1, s), z;
    B *bv;
    I al, as, m = AN(y)/2, j, k = 0, t = 0, *indx = IAV(y), *iv;
    D *dv;
    Z *zv;
    N *atm, *nouns = (N *)a_malloc(sizeof(N)*m);

    DO(m,
       j  = i+i;
       as = indx[j];
       al = indx[j+1];
       atm = &nouns[i];
       ASSERT(parse_atom(al, &s[as], atm), ERLEXER);
       t = MAX(t, NT(atm));
    );
    z = gen_array(t, m!=1, m, NULL);

    NUMERIC_SWITCH(t,
        bv = BAV(z); DO(m, bv[i] = noun_bval(&nouns[i])); break,
        iv = IAV(z); DO(m, iv[i] = noun_ival(&nouns[i])); break,
        dv = DAV(z); DO(m, dv[i] = noun_dval(&nouns[i])); break,
        zv = ZAV(z); DO(m, zv[i] = noun_zval(&nouns[i])); break
    );

    return z;
}
