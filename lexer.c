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
  array_str
  input: String
  output: Boxed String
*/
A array_str(C *str) {
     A z;
     I n = strlen(str)+1;
     z = gen_array(CHAR, 1, n, NULL);
     memcpy(AV(z), str, n);
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
   Generation functions
   input:  Length of word, string to be converted.
   output: Array corresponding to the type of word.
*/
GENERATE(bool) {
     A z;
     C *v;
     I j, wl = n-(n/2);
     z = gen_array(BOOL, 1, wl, NULL);
     v = (C *)AV(z);
     DO(wl, j=i+i; v[i] = s[j]);
     return z;
}

GENERATE(char) {
     A z;
     C *v;
     I j, wl = n-2;
     z = gen_array(CHAR, 1, wl, NULL);
     v = (C *)AV(z);
     s++; /* skip "'" */
     DO(wl, v[i] = s[i]);
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

/*
  token_index
  input:  Boxed string to be lexed.
  output: Array of pairs representing start and end of tokens.
*/
MONAD(token_index) {
     A z; 
     C vec = 0, e, t, s = SS, *str = (C *)AV(y);
     I i, j = 0, n = AN(y), *v;
     ST pr;

     z = gen_array(INT, 1, n+n, NULL);
     v = (I *)AV(z);

     for (i = 0; i < n; i++) {
          t = char_type(str[i]);
          pr = dfa[s][t];
          e = pr.effect;

          switch (e) {
          case EO:  break;
          case EN:  { j = i; break; }
          case EW:  { *v++ = j; *v++ = i-1; j = i; break; }
          case EWR: { *v++ = j; *v++ = i-1; j = -1; break; }
          case EV:  {
               if (!vec) { *v++ = j; *v = i-1; }
               else      { *v = i-1; }
               j = i;
               vec = 1;
               break;
          }
          case EVR: {
               if (!vec) { *v++ = j; *v = i-1; }
               else      { *v = i-1; }
               j = -1;
               vec = 1;
               break;
          }
          case ES:  goto end; break;
          }

          s = pr.new;
     }
end:
     *++v = END;
     return z;
}

/*
  tokens
  input: x: token indicies, start and length.
         y: characters to be tokenized.
  output: List of tokens.
 */
DYAD(tokens) {
     A z;
     C *s = (C *)AV(y);
     I *v = (I *)AV(x);
     return z;
}
