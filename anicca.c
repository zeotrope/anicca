#include "anicca.h"
#include "convert.h"
#include "symbol.h"
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
    a_clean();
    R 0;
}
