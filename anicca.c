#include <stdio.h>
#include <string.h>
#include "anicca.h"
#include "memory.h"
#include "lexer.h"

int main() {
     A x, y;
     I *v;

     x = array_str("*: @ -: @ i. 2 3");
     y = token_index(x);
     v = (I *)AV(y);
     DO(AN(y), printf("%d ", v[i])); printf("\n");

     return 0;
}
