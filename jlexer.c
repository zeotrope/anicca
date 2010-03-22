#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "j.h"
#include "jlexer.h"

buffer buffer_new(I size) {
        buffer buff;
        buff = jmalloc(struct buffer, buffer, 1);
        BP(buff) = 0;
        BS(buff) = size;
        BD(buff) = jmalloc(C, C*, size);
        return buff;
}

buffer buffer_new_str(C *str) {
        buffer buff;
        buff = buffer_new(strlen(str)+1);
        strncpy(buff->data, str, BS(buff) - 1);
        buff->data[BS(buff) - 1] = '\0';
        return buff;
}

V buffer_inspect(buffer buff) {
        printf("pos: %d size: %d contents: ", BP(buff), BS(buff));
        DO(buff->size, printf("%c,", buff->data[i]));
        printf("\n");
}

V buffer_free(buffer buff) {
        if (BS(buff) > 0) {
                free(BD(buff));
                BS(buff) = 0;
        }
}

V buffer_grow(buffer buff, I size) {
        BS(buff) += size;
        BD(buff) = jrealloc(BD(buff), C, C*, BS(buff));
}

V buffer_append(buffer buff, I ch) {
        buffer_grow(buff, 1);
        buff->data[BS(buff) - 2] = ch;
        buff->data[BS(buff) - 1] = '\0';
}

jlexer jlexer_new(C *str) {
        I len;
        jlexer lex;
        len = strlen(str);
        lex = jmalloc(struct jlexer, jlexer, 1);
        LXC(lex) = *str;
        LXSC(lex) = buffer_new_str(str);
        LXSV(lex) = buffer_new_str("");
        return lex;
}

V jlexer_free(jlexer lex) {
        buffer_free(LXSV(lex));
        buffer_free(LXSC(lex));
        free(lex);
}

V jlexer_inspect(jlexer lex) {
        printf("current: %c\n", LXC(lex));
        printf("source=>\n");
        buffer_inspect(LXSC(lex));
        printf("saved=> \n");
        buffer_inspect(LXSV(lex));
}

I jlexer_next_char(jlexer lex) {
        if (LXSC_P(lex) < LXSC_S(lex) - 1) {
                LXSC_P(lex)++;
                LXC(lex) = LXSC(lex)->data[LXSC_P(lex)];
        } else {
                LXC(lex) = EOF;
        }
        return LXC(lex);
}

V jlexer_save_char(jlexer lex, I ch) {
        buffer_append(LXSV(lex), ch);
}

V jlexer_save_curr(jlexer lex) {
        jlexer_save_char(lex, LXC(lex));
}

/* Check graphivz diagram for DFA */
I jlexer_next_token(jlexer lex) {
        DOW(isspace(LXC(lex)), jlexer_next_char(lex));
        
}
