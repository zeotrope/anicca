
OBJS=  memory.o lexer.o atom.o noun.o parser.o verb.o anicca.o
CFLAGS=-ansi -pedantic

all: anicca

anicca: $(OBJS)
	$(CC) -o $@ $(OBJS)

anicca.o: anicca.c anicca.h
verb.o:   verb.c verb.h
parser.o: parser.c parser.h
atom.o:   atom.c atom.h
noun.o:   noun.c noun.h util.h
lexer.o:  lexer.c lexer.h
memory.o: memory.c memory.h

.PHONY clean:
	rm -rf *~ *.o anicca
