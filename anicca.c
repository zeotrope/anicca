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
    a_init();
    a_repl("   ");
    return 0;
}
