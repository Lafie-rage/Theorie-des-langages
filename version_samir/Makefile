YFLAGS=-d
SRCS=hoc.l hoc.y hoc.h symbol.h symbol.c defSymbols.c color.h color.c io.h io.c msgFmt.c
OBJS=hoc.o hoc.l.o symbol.o color.o io.o
CC=gcc

hoc: $(OBJS)
	gcc $(OBJS) -o hoc -ll -ly -lm
	make clean
	
hoc.o: hoc.h symbol.h io.h hoc.y
	bison $(YFLAGS) hoc.y
	mv hoc.tab.c hoc.c
	gcc -c hoc.c

hoc.l.o: hoc.h hoc.tab.h symbol.h io.h hoc.l
	flex -I hoc.l
	gcc -c lex.yy.c -o hoc.l.o
	rm lex.yy.c

symbol.o: hoc.h hoc.tab.h symbol.h symbol.c defSymbols.c
	gcc -c symbol.c

color.o: hoc.h color.h color.c
	gcc -c color.c

io.o: hoc.h symbol.h color.h io.h io.c msgFmt.c
	gcc -c io.c

clean:
	rm -f $(OBJS) hoc.tab.h hoc.c lex.yy.c *~

edit:
	gedit $(SRC) &
