
.PHONY: all clean

all: lang.pdf lex.pdf

lang.pdf: lang.tex
	pdflatex $<

lex.pdf: lex.dot
	dot -Tpdf $< -o $@

clean:
	rm -rf lang.pdf lang.log lang.aux lex.pdf