CC ?= gcc
CXX ?= g++
PREFIX ?= /usr/local
DESTDIR ?=
all:
	mkdir -p build
	$(CC) -O2 -c src/tokenizer.c -o build/tokenizer.o
	$(CXX) -O2 src/simplecalculator.cpp build/tokenizer.o -o build/calc

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp build/calc $(DESTDIR)$(PREFIX)/bin/

clean:
	rm -rf build
