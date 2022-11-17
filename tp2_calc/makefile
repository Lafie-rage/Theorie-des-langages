all: v0_5

# v0.5

v0_5: calc_lex_v0_5
	gcc calc.tab.c calc.yy.c -o calc -ll -ly

calc_lex_v0_5: calc_v0.5.l calc_bison_v0_5 calc.tab.h
	lex -o calc.yy.c $<

calc_bison_v0_5: calc_v0.5.y
	bison -d -o calc.tab.c $^

# v0.4

v0_4: calc_lex_v0_4
	gcc calc.tab.c calc.yy.c -o calc -ll -ly

calc_lex_v0_4: calc_v0.4.l calc_bison_v0_4 calc.tab.h
	lex -o calc.yy.c $<

calc_bison_v0_4: calc_v0.4.y
	bison -d -o calc.tab.c $^

# v0.3

v0_3: calc_lex_v0_3
	gcc calc.tab.c calc.yy.c -o calc -ll -ly

calc_lex_v0_3: calc_v0.3.l calc_bison_v0_3 calc.tab.h
	lex -o calc.yy.c $<

calc_bison_v0_3: calc_v0.3.y
	bison -d -o calc.tab.c $^

# v0.3 MAIS PAS VRAIMENT

v0_3_mais_pas_vraiment: calc_lex_v0_3_mais_pas_vraiment
	gcc calc.tab.c calc.yy.c -o calc -ll -ly

calc_lex_v0_3_mais_pas_vraiment: calc_v0.3_mais_pas_vraiment.l calc_bison_v0_3_mais_pas_vraiment calc.tab.h
	lex -o calc.yy.c $<

calc_bison_v0_3_mais_pas_vraiment: calc_v0.3_mais_pas_vraiment.y
	bison -d -o calc.tab.c $^

# v0.2

v0_2: calc_lex_v0_2
	gcc calcv0.2.yy.c -o calc -ll

calc_lex_v0_2: calc_v0.2.l
	lex -o calcv0.2.yy.c $^

# v0.1

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
