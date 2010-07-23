#ifndef _ERROR_H
#define _ERROR_H

#define NERRS 2

typedef enum {
    ERDOM,
    ERRANK
} ERRS;

static C *errors[NERRS] = {
    "domain error",
    "rank error"
};

#define ASSERT(cond, err) \
    if (!(cond)) { a_signal(err); }

#endif
