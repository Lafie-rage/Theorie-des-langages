all: wc_lex
	gcc lex.yy.c -o wc -ll

example: example_lex
	gcc lex.yy.c -o example -ll

wc_lex: wc.l
	lex $^

example_lex: example.l
	lex $^
