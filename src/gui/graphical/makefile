CFLAGS ?= -O0
CXXFLAGS ?= -O0

test:graphics.o test.cpp
	g++ $(CXXFLAGS) -g -lncurses test.cpp graphic-constants.h graphics.o -o test

graphics.o:graphics.c
	gcc $(CFLAGS) -lncurses -c -g  graphics.c -o graphics.o

ass:
	gcc $(CFLAGS) -lncurses -S graphics.c -o graphics.o


clean:
	rm graphics.o
	rm test
	rm a-graphics.i  a-graphics.o  a-graphics.s