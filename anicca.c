#include <stdio.h>
#include <string.h>

#include "anicca.h"
#include "char.h"
#include "memory.h"
#include "function.h"
#include "verb.h"
#include "adverb.h"
#include "primitive.h"
#include "lexer.h"
#include "parser.h"
#include "util.h"

I main(I argc, C *argv[]) {
    A x, y, z;
    C *s = "1 2 3";

    a_init();
    x = eval(argv[1] ? argv[1] : s);
    println(x);

    return 0;
}
