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
     I n = strlen(str);
     z = gen_array(CHAR, 1, n, NULL);
     memcpy(AV(z), str, n);
     return z;
}

/*
  token_index
  input:  Boxed string to be lexed.
  output: Array of pairs representing start and length of tokens.
*/
MONAD(token_index) {
     A z; 
     C e, t, s = SS, *str = (C *)AV(y);
     I i, j = 0, n = AN(y), *v;
     ST pr;

     z = gen_array(INT, 1, n+n, NULL);
     v = (I *)AV(z);
        
     for (i = 0; i < n; i++) {
          t = char_type(str[i]);
          pr = dfa[s][t];
          e = pr.effect;
          printf("%d %d - %d %d %d\n", s, t, e, i, j);
          if (e == EI) {
               j = i;
          }
          else if (e == EN) {
               *v++ = j;
               *v++ = (i-1) - j;
               j = i;
          }
          s = pr.new;
     }

     return z;
}
