#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "anicca.h"
#include "memory.h"
#include "lexer.h"
#include "noun.h"

/* 
   Generation functions
   input:  Length of string, String to be converted.
   output: Noun with corresponding value and type.
*/
GENERATE(char) {
    A z;
    C *v;

    s++; n-=2;
    z = gen_array(CHAR, 1, n, NULL);
    v = (C *)AV(z);
    if (n > 0) { strncpy(v, s, n); }

    return z;
}


/*
  noun_start
  input:  Length of noun, String of noun.
  output: Array in the form:
  [number of tokens, start index token 1, length token 1, start index token 2,
  length token 2, ..., start index token n, length token n].
*/
A noun_index(I n, C *s) {
    A z;
    C st = SS, e, t;
    I m = 1+n, k = 1, j = 1, i, *v;
    ST pr;

    z = gen_array(INT, 1, m, NULL);
    v = (I *)AV(z);

    for (i = 0; i < n; i++) {
        t = nountype[s[i]];
        pr = noun[st][t];
        e = pr.effect;
        st = pr.new;

        switch (e) {
        case EO: break;
        case EN: j = i; break;
        case EW: v[k++] = j; v[k++] = i-j; break;
        case ES: goto end_noun; break;
        }
    }
  end_noun:    
    v[0] = k/2;
    return z;
}

/*
  token_index
  input:  Boxed string to be lexed.
  output: Array in the form:
  [number of tokens, start index token 1, length token 1, start index token 2,
  length token 2, ..., start index token n, length token n].
*/
MONAD(token_index) {
    A z; 
    C vec = 0, e, t, s = SS, sn, *str = (C *)AV(y);
    I i, jv, j = 0, k = 1, n = AN(y), *v;
    ST pr;

    z = gen_array(INT, 1, n+n, NULL);
    v = (I *)AV(z);

    for (i = 0; i < n; i++) {
        t = chartype[str[i]];
        pr = dfa[s][t];
        e = pr.effect;
        sn = pr.new;

        switch (e) {
        case EO: break;
        case EN: { j = i; break; }
        case EW: { v[k++] = j; v[k++] = i-j; j = i; break; }
        case EY: { v[k++] = j; v[k++] = i-j; j = -1; break; }
        case EV: {
            if (!vec) { v[k++] = j; v[k] = i-1; jv = j; }
            else      { v[k] = i-jv; }
            j = i;
            vec = 1;
            break;
        }
        case EZ: {
            if (!vec) { v[k++] = j; v[k] = i-1; jv = j; }
            else      { v[k] = i-jv; }
            j = -1;
            vec = 1;
            break;
        }
        case ES: goto end; break;
        }

        if (vec && sn != S9 && sn != SS) {
            vec = 0; k++;
        }

        s = sn;
    }
  end:
    v[0] = k/2;
    return z;
}

/*
  tokens
  input:
    x: Output of token_index.
    y: Boxed string to be tokenized.
  output: List of tokens.
*/
DYAD(tokens) {
    A z, *av;
    C *s, *str = (C *)AV(y);
    I i, ws, wl, n, t, *v = (I *)AV(x);

    n = *v++;
    z = gen_array(BOX, 1, n+5, NULL);
    av = (A *)AV(z);

    for (i = 0; i < n; i++) {
        ws = v[i];
        wl = v[i+1];
        s = &str[ws];
        t = chartype[*s];

        switch (t) {
        case C9: {
            *av++ = parse_noun(wl, s);
            break;
        }
        case CQ: {
            *av++ = gen_char(wl, s);
            break;
        }
        }
    }

    DO(5, *av++ = mark);
    return z;
}
