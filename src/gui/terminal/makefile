

test:render.o
	g++ -lncurses test.cpp terminal-constants.h render.o -o test

render.o:render.c
	gcc -lncurses -c  render.c -o render.o


clean:
	rm render.o
	rm test
