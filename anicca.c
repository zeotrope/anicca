#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "anicca.h"
#include "char.h"
#include "memory.h"
#include "convert.h"
#include "function.h"
#include "verb.h"
#include "adverb.h"
#include "conjunction.h"
#include "primitive.h"
#include "lexer.h"
#include "parser.h"
#include "util.h"


I main(I argc, C *argv[]) {
    C *v, str[100];
    A x, y, z;

    a_init();
    while (1) {
        printf("   ");
        fgets(str, 100, stdin);
        v = strndup(str, strlen(str)-1); /* remove carriage return */
        println(z = eval(v));
    }
    return 0;
}
