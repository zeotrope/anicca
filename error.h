#ifndef _ERROR_H
#define _ERROR_H

typedef enum {
    ERDOM=0,
    ERRANK,
    ERLEN,
    ERLIMIT,
    ERLEXER,
    ERSYNTAX,
    ERILLNUM,
    ERILLNAME,
    ERASGN,
    ERVALUE,
    ERCONV,
    ERMEMLT,
    ERALLOC,
    NERRS
} ERRS;

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

#define ASSERT(cond, err) \
    if (!(cond)) { a_signal(err); }

#endif
