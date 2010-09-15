#include "anicca.h"

static C *errors[NERRS] = {
    "domain error",
    "rank error",
    "length error",
    "limit error",
    "lexical error",
    "syntax error",
    "ill-formed number",
    "ill-formed name",
    "assignment error",
    "value error",
    "conversion error",
    "memory limit",
    "allocation error"
};

VO a_signal(C err) {
    fprintf(stderr, "|");
    fprintf(stderr, "%s\n", errors[err]);
    fprintf(stderr, "|\n");
}
