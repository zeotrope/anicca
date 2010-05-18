#include <stdio.h>
#include <string.h>
#include "anicca.h"
#include "memory.h"
#include "lexer.h"
#include "verb.h"

V print(A y) {
     C *cv;
     I *iv;
     switch (AT(y)) {
     case BOOL: {
          cv = (B *)AV(y);
          DO(AN(y), printf("%d ", (I)cv[i]));
          break;
     }
     case CHAR: {
          cv = (C *)AV(y);
          DO(AN(y), printf("%c", cv[i]));
          break;
     }
     case INT: {
          iv = (I *)AV(y);
          DO(AN(y), printf("%d ", iv[i]));
          break;
     }
     }
     printf("\n");
}

V a_init(V) {
     mark = gen_array(MARK, 0, 0, NULL);
}

int main() {
     A y, z;
     char *s = "12 23";
     y = noun_start(6, s);
     //z = gen_int(y, s);
     print(y);
     return 0;
}
