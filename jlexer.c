/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*----------------------------------------------------------------------------*/
#include "j.h"
#include "jmemory.h"
#include "buffer.h"
#include "jlexer.h"
/*----------------------------------------------------------------------------*/

/*============================================================================*/

jlexer jlexer_new(C *str) {
        I len;
        jlexer lex;
        len = strlen(str);
        lex = jmalloc(struct _jlexer, jlexer, 1);
        LXC(lex) = *str;
        LXSC(lex) = buffer_new_str(str);
        LXSV(lex) = buffer_new_str("");
        return lex;
}
/*============================================================================*/

V jlexer_free(jlexer lex) {
        buffer_free(LXSV(lex));
        buffer_free(LXSC(lex));
        free(lex);
}
/*============================================================================*/

I jlexer_next_char(jlexer lex) {
        if (LXSC_P(lex) < LXSC_S(lex) - 1) {
                LXSC_P(lex)++;
                LXC(lex) = LXSC(lex)->data[LXSC_P(lex)];
        } else {
                LXC(lex) = EOF;
        }
        return LXC(lex);
}
/*============================================================================*/

V jlexer_save_char(jlexer lex, I ch) {
        buffer_append(LXSV(lex), ch);
}
/*============================================================================*/

V jlexer_save_curr(jlexer lex) {
        jlexer_save_char(lex, LXC(lex));
}
/*============================================================================*/

/* Check graphivz diagram for DFA */
I jlexer_next_token(jlexer lex) {
        DOW(isspace(LXC(lex)), jlexer_next_char(lex));
        
}
/*============================================================================*/
