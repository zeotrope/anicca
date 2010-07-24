#include <stdio.h>
#include <string.h>

#include "anicca.h"
#include "char.h"
#include "memory.h"
#include "function.h"
#include "verb.h"
#include "adverb.h"
#include "conjunction.h"
#include "primitive.h"
#include "lexer.h"
#include "parser.h"
#include "util.h"

I main(I argc, C *argv[]) {
    C str[100];
    A x, y, z;

    a_init();
    while (1) {
        printf("   ");
        fgets(str, 100, stdin);
        x = array_str(strlen(str), str);
        y = parse(tokens(token_index(x), x));
        println(y);
        a_free(x); a_free(y);
    }
    return 0;
}
