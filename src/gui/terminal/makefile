

test:render.o
	g++ -lncurses test.cpp render.o -o test

render.o:clean
	gcc -lncurses -c render.c -o render.o

clean:
	rm render.o
	rm test
