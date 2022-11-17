all: v0_3

v0_3: calc_lex_v0_3
	gcc calc.tab.c calc.yy.c -o calc -ll -ly

calc_lex_v0_3: calc_v0.3.l calc_bison_v0_3
	lex -o calc.yy.c calc_v0.3.l

calc_bison_v0_3: calc_v0.3.y
	bison -d -o calc.tab.c $^

v0_2: calc_lex_v0_2
	gcc calcv0.2.yy.c -o calc -ll

calc_lex_v0_2: calc_v0.2.l
	lex -o calcv0.2.yy.c $^

v0_1: calc_lex_v0_1
	gcc calcv0.1.yy.c -o calc -ll

calc_lex_v0_1: calc_v0.1.l
	lex -o calcv0.1.yy.c $^

clean: clean_lex
	rm calc

clean_lex: clean_bison
	rm *.yy.c

clean_bison:
	rm *.tab.*
