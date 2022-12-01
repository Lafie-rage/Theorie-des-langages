all: v1

# v1
v1: hoc_lex_v1 symbol.c
	gcc hoc.tab.c symbol.c hoc.yy.c -o hoc -ll -ly

hoc_lex_v1: hoc_v1.0.l hoc_bison_v1 hoc.tab.h
	lex -o hoc.yy.c $<

hoc_bison_v1: hoc_v1.0.y
	bison -d -o hoc.tab.c $^

# CLEAN

clean: clean_lex
	rm hoc

clean_lex: clean_bison
	rm *.yy.c

clean_bison:
	rm *.tab.*
