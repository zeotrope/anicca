#include <stdio.h>

#include "anicca.h"
#include "error.h"

VO a_signal(C err) {
    fprintf(stderr, "|");
    fprintf(stderr, "%s\n", errors[err]);
    fprintf(stderr, "|\n");
}
