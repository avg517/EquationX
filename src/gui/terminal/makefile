CFLAGS ?= -O0
CXXFLAGS ?= -O0

test:render.o test.cpp
	g++ $(CXXFLAGS) -g -lncurses test.cpp terminal-constants.h render.o -o test

render.o:render.c
	gcc $(CFLAGS) -lncurses -c -g  render.c -o render.o

ass:
	gcc $(CFLAGS) -lncurses -S render.c -o render.o


clean:
	rm render.o
	rm test
	rm a-render.i  a-render.o  a-render.s
