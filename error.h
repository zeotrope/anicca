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

#define ASSERT(cond, err) \
    if (!(cond)) { a_signal(err); }

#endif
