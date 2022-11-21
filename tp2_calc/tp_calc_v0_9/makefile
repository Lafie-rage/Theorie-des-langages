all: v0_9

# v0.9

v0_9: calc_lex_v0_9
	gcc calc.tab.c symbol.c calc.yy.c -o calc -ll -ly

calc_lex_v0_9: calc_v0.9.l calc_bison_v0_9 calc.tab.h
	lex -o calc.yy.c $<

calc_bison_v0_9: calc_v0.9.y
	bison -d -o calc.tab.c $^

# CLEAN

clean: clean_lex
	rm calc

clean_lex: clean_bison
	rm *.yy.c

clean_bison:
	rm *.tab.*
