
all: j

j: main.o jlexer.o
	$(CC) main.o jlexer.o -o $@

main.o: main.c j.h
	$(CC) -c -o $@ $<

jlexer.o: jlexer.c j.h
	$(CC) -c -o $@ $<

clean-doc:
	rm -rf ./doc/lang.pdf ./doc/lang.aux ./doc/lang.log

clean: clean-doc
	rm -rf *.o *~ j