all : lex.yy.c
	gcc lex.yy.c -o example -ll

lex.yy.c : example.l
	lex $^
