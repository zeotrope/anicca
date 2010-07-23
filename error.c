#include <stdio.h>

#include "anicca.h"
#include "error.h"

VO a_signal(C err) {
    printf("|");
    printf("%s\n", errors[err]);
    printf("|\n");
}
