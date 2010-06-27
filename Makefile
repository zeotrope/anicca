
OBJS=  memory.o atom.o noun.o verb.o primitive.o lexer.o parser.o anicca.o
CFLAGS=-ansi -pedantic -g3

all: anicca

anicca: $(OBJS)
	$(CC) -o $@ $(OBJS)

anicca.o:    anicca.c anicca.h
parser.o:    parser.c parser.h
lexer.o:     lexer.c lexer.h char.h table.h primitive.h
verb.o:      verb.c verb.h
primitive.o: primitive.c primitive.h verb.h
noun.o:      noun.c noun.h util.h
atom.o:      atom.c atom.h noun.h
memory.o:    memory.c memory.h

.PHONY clean:
	rm -rf *~ *.o anicca
