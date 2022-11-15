all: calc_lex
	gcc calc.yy.c -o calc -ll

calc_lex: calc_v0.1.l
	lex -o calc.yy.c $^

clean:
	rm *.yy.c
	rm calc
