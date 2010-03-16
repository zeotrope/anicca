
all: j

j: main.o jlexer.o
	$(CC) main.o jlexer.o -o $@

main.o: main.c j.h
	$(CC) -c -o $@ $<

jlexer.o: jlexer.c j.h
	$(CC) -c -o $@ $<

.PHONY clean:
	rm -rf *.o *~ j