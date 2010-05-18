#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "anicca.h"
#include "memory.h"
#include "lexer.h"

/* 
   Generation functions
   input:  Length of word, string to be converted.
   output: Array corresponding to the type of word.
*/
GENPRIM(bool) {
     A z;
     B *v;
     I *indx = (I *)AV(y), m = *indx++;
     
     z = gen_array(BOOL, 1, m, NULL);
     v = (B *)AV(z);
     DO(m, v[i] = (s[indx[i]]=='_') ? -(s[indx[i]+1]-'0'):s[indx[i]]-'0');

     return z;
}

GENPRIM(int) {
     A z;
     I si, num, *v, *indx = (I *)AV(y), m = *indx++;
     
     z = gen_array(INT, 1, m, NULL);
     printf("%d\n", m);
     DO(m,
        //s[indx[i]] = (s[indx[i]]=='_' ? '-' : s[indx[i]]);
        printf("%d %d %d\n", i, indx[i], indx[i+1]);
        v[i] = strtol(s+indx[i], NULL, 10);
          );

     return z;
}

GENPRIM(flt) {
     A z; return z;
}

GENPRIM(cmp) {
     A z; return z;
}

GENERATE(num) {
     A y, z;
     y = noun_start(n, s);
     return z;
}

GENERATE(char) {
     A z;
     C *v;

     s++; n-=2;
     z = gen_array(CHAR, 1, n, NULL);
     v = (C *)AV(z);

     if (n > 0) {
          strncpy(v, s, n);
     }
     return z;
}

/*
  token_index
  input:  Boxed string to be lexed.
  output: Number of pairs ; Array of pairs, start and length of tokens.
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
          case EO:  break;
          case EN:  { j = i; break; }
          case EW:  { v[k++] = j; v[k++] = i-j; j = i; break; }
          case EWR: { v[k++] = j; v[k++] = i-j; j = -1; break; }
          case EV:  {
               if (!vec) { v[k++] = j; v[k] = i-1; jv = j; }
               else      { v[k] = i-jv; }
               j = i;
               vec = 1;
               break;
          }
          case EVR: {
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
     v[0] = k-1;
     return z;
}

/* 
   noun_start
   input:  String of noun.
   output: Number of nouns ; Start indicies of atomic nouns within string.
*/
A noun_start(I n, C *s) {
     A z;
     C st = SS, e, t;
     I m = 1+n, k = 1, j = 1, i, *v;
     ST pr;

     z = gen_array(INT, 1, m, NULL);
     v = (I *)AV(z);

     for (i = 0; i < n; i++) {
          t = chartype[s[i]];
          t = (t!=CS && t!=CX);
          pr = noun[st][t];
          e = pr.effect;
          
          switch (e) {
          case EO: break;
          case EN: j = i; break;
          case EW: v[k++] = j; v[k++] = i-j; break;
          }

          st = pr.new;
     }
     
     v[0] = k/2;
     return z;
}

/*
  tokens
  input: x: token indicies, start and length.
         y: characters to be tokenized.
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
             *av++ = gen_num(wl, s);
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
