#include <stdio.h>
#include <string.h>
#include "anicca.h"
#include "memory.h"
#include "lexer.h"

int main() {
     A x, y;
     x = array_str("1.23+2");
     y = token_index(x);
     array_inspect(y);
     return 0;
}
