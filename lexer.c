#include <stdio.h>
#include <stdlib.h>
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
  token_index
  input:  Boxed string to be lexed.
  output: Pair representing start and length of token.
*/
MONAD(token_index) {
        A z; 
        C e, s = SS, *str = (C *)AV(y);
        I i, j = 0, n = AN(y), *v;
        ST pr;

        z = gen_array(INT, 1, n+n, NULL);
        v = (I *)AV(z);
        
        for (i = 0; i < n; i++) {
                pr = dfa[s][char_type(str[i])];
                e = pr.effect;

                if (e == EI) {
                        j = i;
                }
                else if (e == EN) {
                        *v++ = j;
                        *v++ = (i-1) - j;
                        j = i;
                }
        }

        return z;
}
