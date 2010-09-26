#include <ctype.h>

#include "anicca.h"
#include "verb.h"
#include "adverb.h"
#include "conjunction.h"
#include "noun.h"
#include "lexer.h"
#include "primitive.h"

#define DCOL 9
#define DROW 10

static ST dfa[DROW][DCOL] = {
/*SS*/ {{SX,EN},{SS,EO},{SA,EN},{SN,EN},{SA,EN},{S9,EN},{SX,EN},{SX,EN},{SQ,EN}},
/*SX*/ {{SX,EW},{SS,EY},{SA,EW},{SN,EW},{SA,EW},{S9,EW},{SX,EO},{SX,EO},{SQ,EW}},
/*SA*/ {{SX,EW},{SS,EY},{SA,EO},{SA,EO},{SA,EO},{SA,EO},{SX,EO},{SX,EO},{SQ,EW}},
/*SN*/ {{SX,EW},{SS,EY},{SA,EO},{SA,EO},{SM,EO},{SA,EO},{SX,EO},{SX,EO},{SQ,EW}},
/*SM*/ {{SX,EW},{SS,EY},{SA,EO},{SA,EO},{SA,EO},{SA,EO},{SO,EO},{SX,EO},{SQ,EW}},
/*SO*/ {{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SX,EO},{SX,EO},{SZ,EO}},
/*S9*/ {{SX,EV},{SS,EZ},{S9,EO},{S9,EO},{S9,EO},{S9,EO},{S9,EO},{SX,EO},{SQ,EV}},
/*SQ*/ {{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SQ,EO},{SC,EO}},
/*SC*/ {{SX,EW},{SS,EY},{SA,EW},{SN,EW},{SA,EW},{S9,EW},{SX,EW},{SX,EW},{SQ,EO}},
/*SZ*/ {{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO},{SZ,EO}}
       /* CX      CS      CA      CN      CB      C9      CD      CC      CQ   */
};

/* parse_literal
     input:  (1)Length of string, (2)Pointer to string.
     output: Array of type string with length (n-2). */
static A parse_literal(I n, C *s) { A z=gstr(n-=2,++s); R z; }

/* parse_name
     input:  (1)Length of string, (2)Pointer to string.
     output: Array of type name. */
static A parse_name(I n, C *s) { A z=gnm(n,s); R z; }

/* token_index
     input:  Boxed string to be lexed.
     output: Array of size 2n (n = number of tokens), in the form:
       [start index token 1, length token 1, start index token 2,
       length token 2, ..., start index token n, length token n]. */
static MONAD(token_index) { A z; ST pr;
    C e, sn, t, s=SS, vec=0, *str=CAV(y);
    I i, jv, j=0, k=0, n=AN(y), *v;
    z=ga(INT,1,2*n,NULL); v=IAV(z);

    DO(n, t=ctype(str[i]); pr=dfa[s][t];
       e=pr.effect; sn=pr.new;

       switch (e) {
       case EO: break;
       case EN: { j=i; break; }
       case EW: { v[k++]=j; v[k++]=i-j; j=i;  break; }
       case EY: { v[k++]=j; v[k++]=i-j; j=-1; break; }
       case EV: {
           if (!vec) { v[k++]=j; v[k]=i-j; jv=j; }
           else      { v[k]=i-jv; }
           j=i; vec=1; break;
       }
       case EZ: {
           if (!vec) { v[k++]=j; v[k]=i-j; jv=j; }
           else      { v[k]=i-jv; }
           j=-1; vec=1; break;
       }
       case ES: goto end; break;
       }

       if (vec && sn!=S9 && sn!=SS) { vec=0; k++; }
       s=sn;
    );
  end:
    z=ra(z,INT,k); R z;
}

/* tokens
     input:  Boxed string to be tokenized.
     output: Array of boxed tokens. */
MONAD(tokens) { A x=token_index(y), v, z, *av;
    C c, vn, *str=CAV(y), *s;
    I n=AN(x)/2, *indx=IAV(x), j, ws, wl, t;
    z=ga(BOX,1,n+5,NULL); av=AAV(z); *av++=mark;

    DO(n, j=i+i; ws=indx[j]; wl=indx[j+1];
       s=&str[ws]; c=*s; t=ctype(c);
       vn=verb_name(wl,s); v=primitive_lookup(vn);

       if (AT(v)&MARK) {
           switch (t) {
           case CS:
           case C9: { *av++ = parse_noun(wl,s);    break; }
           case CQ: { *av++ = parse_literal(wl,s); break; }
           case CA: { *av++ = parse_name(wl,s);    break; }
           default: break; /* error */
           }
       }
       else { *av++=v; }
    );

    DO(4, *av++=mark); R z;
}
