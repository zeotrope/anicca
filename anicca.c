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
     I *v;
     A x, y, z, q, p;
     a_init();
     y = gen_bool(6, "_1 0 1");
     print(y);
     return 0;
}
