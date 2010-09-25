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

I main(I argc, C *argv[]) { A y, cl;
    a_init();
    y=eval("i.2 2 3");
    println(cl=cells(y,1));
    a_repl("   ");
    a_clean();
    R 0;
}
