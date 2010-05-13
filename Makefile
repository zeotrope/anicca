
OBJS=  memory.o lexer.o verb.o anicca.o

all: anicca

anicca: $(OBJS)
	$(CC) -o $@ $(OBJS)

anicca.o: anicca.c anicca.h
	$(CC) -c -o $@ $<

verb.o: verb.c verb.h
	$(CC) -c -o $@ $<

lexer.o: lexer.c lexer.h
	$(CC) -c -o $@ $<

memory.o: memory.c memory.h
	$(CC) -c -o $@ $<

.PHONY clean:
	rm -rf *~ *.o anicca