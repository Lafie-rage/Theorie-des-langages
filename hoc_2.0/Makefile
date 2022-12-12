YFLAGS=-d
SRCS=hoc.l hoc.y hoc.h symbol.h symbol.c defSymbols.c color.h color.c io.h io.c msgFmt.c codeHoc.h codeHoc.c code.h code.c
OBJS=hoc.o hoc.l.o symbol.o color.o io.o codeHoc.o code.o
CC=gcc
DBG=-D DBG_CODE

hoc: $(OBJS)
	gcc $(OBJS) -o hoc -ll -ly -lm
	make clean

hoc.o: hoc.h symbol.h io.h hoc.y
	bison $(YFLAGS) hoc.y
	mv hoc.tab.c hoc.c
	gcc $(DBG) -c hoc.c

hoc.l.o: hoc.h hoc.tab.h symbol.h io.h hoc.l
	flex -I hoc.l
	gcc $(DBG) -c lex.yy.c -o hoc.l.o
	rm lex.yy.c

symbol.o: hoc.h hoc.tab.h symbol.h symbol.c defSymbols.c
	gcc $(DBG) -c symbol.c

color.o: hoc.h color.h color.c
	gcc $(DBG) -c color.c

io.o: hoc.h symbol.h color.h io.h io.c msgFmt.c
	gcc $(DBG) -c io.c

codeHoc.o: hoc.h io.h io.c codeHoc.h codeHoc.c
	gcc $(DBG) -c codeHoc.c

code.o: hoc.h io.h io.c codeHoc.h codeHoc.c code.h code.c
	gcc $(DBG) -c code.c

clean:
	rm -f $(OBJS) hoc.c lex.yy.c *~

edit:
	gedit $(SRC) &
