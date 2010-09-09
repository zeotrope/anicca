
HDRS= types.h char.h table.h

OBJS= memory.o util.o error.o convert.o noun.o function.o symbol.o verb.o \
      verb-scalar1.o verb-scalar2.o verb-atomic.o primitive.o adverb.o    \
      conjunction.o lexer.o parser.o test.o anicca.o

CFLAGS=-ansi -pedantic -O3

all: anicca

anicca: $(HDRS) $(OBJS)
	$(CC) -o $@ $(OBJS) -lm

debug: CFLAGS = -ansi -pedantic -g3 -DDEBUG
debug: anicca

.o: .c .h
	$(CC) -c $<

.PHONY clean:
	rm -rf *~ *.o anicca
