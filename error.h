#ifndef _ERROR_H
#define _ERROR_H

typedef enum {
    ERDOM,
    ERRANK,    
    ERLEXER,
    ERSYNTX,
    ERILLNUM,
    ERALLOC,
    NERRS
} ERRS;

static C *errors[NERRS] = {
    "domain error",
    "rank error",
    "lexical error",
    "syntax error",
    "ill-formed number",
    "allocation error"
};

#define ASSERT(cond, err) \
    if (!(cond)) { a_signal(err); }

#endif
