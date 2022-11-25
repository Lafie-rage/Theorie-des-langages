all: v1

# v1

v1: calc_lex_v1 symbol.c
	gcc calc.tab.c symbol.c calc.yy.c -o calc -ll -ly

calc_lex_v1: calc_v1.0.l calc_bison_v1 calc.tab.h
	lex -o calc.yy.c $<

calc_bison_v1: calc_v1.0.y
	bison -d -o calc.tab.c $^

# CLEAN

clean: clean_lex
	rm calc

clean_lex: clean_bison
	rm *.yy.c

clean_bison:
	rm *.tab.*
