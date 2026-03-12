CC ?= gcc
CXX ?= g++
PREFIX ?= /usr/local
DESTDIR ?=
CFLAGS ?= -g 
CXXFLAGS ?= -g -DFUNC_LOGS
all:
	mkdir -p build
	$(CC) $(CFLAGS) -c src/tokenizer.c -o build/tokenizer.o
	$(CXX) $(CXXFLAGS) src/simplecalculator.cpp build/tokenizer.o -o build/calc
	$(CXX) $(CXXFLAGS) src/testfunctioncreation.cpp -o build/functest
install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp build/calc $(DESTDIR)$(PREFIX)/bin/
	cp build/functest $(DESTDIR)$(PREFIX)/bin/
clean:
	rm -rf build
