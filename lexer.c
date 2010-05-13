#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "anicca.h"
#include "memory.h"
#include "lexer.h"

/*
  char_type
  input:  A character
  output: Type of the character as specified in enum CHARTYPE
*/
CHARTYPE char_type(C c) {
     if (isspace(c)) {
          return CS;
     }
     else if (isalpha(c)) {
          return CA;
     }
     else if (isdigit(c) || c == '_') {
          return C9;
     }
     else if (c == 'N') {
          return CN;
     }
     else if (c == 'B') {
          return CB;
     }
     else if (c == '.') {
          return CD;
     }
     else if (c == ':') {
          return CC;
     }
     else if (c == '\'') {
          return CQ;
     }
     else {
          return CX;
     }
}

/* 
   Generation functions
   input:  Length of word, string to be converted.
   output: Array corresponding to the type of word.
*/
GENERATE(bool) {
     A z; return z;
}

GENERATE(char) {
     A z;
     C *v;
     s++; n-=2;
     z = gen_array(CHAR, 1, n, NULL);
     v = (C *)AV(z);
     strncpy(v, s, n);
     return z;
}

GENERATE(int) {
     A z; return z;
}

GENERATE(flt) {
     A z; return z;
}

GENERATE(cmp) {
     A z; return z;
}

GENERATE(num) {
     A z; return z;
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
          t = char_type(str[i]);
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
   word_start
   input:  String of noun.
   output: List of start indicies of individual nouns within string.
*/
A word_start(I n, C *s) {
     A z;
     I a;
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
     
     n = v[0];
     z = gen_array(BOX, 1, n+5, NULL);
     av = (A *)AV(z);

     for (i = 1; i < n; i++) {
        ws = v[i];
        wl = v[i+1];
        s = &str[ws];
        t = char_type(*s);

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
