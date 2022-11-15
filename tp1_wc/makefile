all: wc_lex
	gcc wc.yy.c -o wc -ll

example: example_lex
	gcc example.yy.c -o example -ll

wc_lex: wc.l
	lex -o wc.yy.c $^

example_lex: example.l
	lex -o example.yy.c $^

clean:
	rm *.yy.c
	rm wc
	rm example
