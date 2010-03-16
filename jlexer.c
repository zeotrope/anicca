#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "j.h"
#include "jlexer.h"

buffer buffer_new(I size) {
        buffer buff;
        buff = (buffer)jmalloc(struct buffer, 1);
        buff->pos = 0;
        buff->size = size;
        buff->data = (C *)jmalloc(char, size);
        return buff;
}

buffer buffer_new_str(char *str) {
        buffer buff;
        buff = buffer_new(strlen(str)+1);
        strncpy(buff->data, str, buff->size - 1);
        buff->data[buff->size - 1] = '\0';
        return buff;
}

V buffer_inspect(buffer buff) {
        if (buff == NULL) {
                printf("NULL\n");
        }
        else {
                printf("pos: %d size: %d contents: ", buff->pos, buff->size);
                DO(buff->size, printf("%c,", buff->data[i]));
                printf("\n");
        }
}

V buffer_free(buffer buff) {
        if (buff->size > 0) {
                free(buff->data);
        }
        free(buff);
}

V buffer_grow(buffer buff, I size) {
        buff->size += size;
        buff->data = (C *)jrealloc(buff->data, C, buff->size);
}

V buffer_append(buffer buff, I ch) {
        buffer_grow(buff, 1);
        buff->data[buff->size - 2] = ch;
        buff->data[buff->size - 1] = '\0';
}

jlexer jlexer_new(C *str) {
        I len;
        jlexer lex;
        len = strlen(str);
        lex = (jlexer)jmalloc(struct jlexer, 1);
        lex->c = *str;
        lex->src = buffer_new_str(str);
        lex->saved = buffer_new_str("");
        return lex;
}

V jlexer_free(jlexer lex) {
        buffer_free(lex->saved);
        buffer_free(lex->src);
        free(lex);
}

V jlexer_inspect(jlexer lex) {
        printf("current: %c\n", lex->c);
        printf("source=>\n");
        buffer_inspect(lex->src);
        printf("saved=> \n");
        buffer_inspect(lex->saved);
}

I jlexer_next_char(jlexer lex) {
        if (lex->src->pos < lex->src->size - 1) {
                lex->src->pos++;
                lex->c = *(lex->src->data + lex->src->pos);
        } else {
                lex->c = EOF;
        }
        return lex->c;
}

V jlexer_save_char(jlexer lex, I ch) {
        buffer_append(lex->saved, ch);
}

V jlexer_save_curr(jlexer lex) {
        jlexer_save_char(lex, lex->c);
}

I jlexer_next_token(jlexer lex) {
        I token;

        while (isspace(lex->c)) {
                jlexer_next_char(lex);
        }

        if (isdigit(lex->c)) {
                do {

                } while (isdigit(lex->c));
        }
}
