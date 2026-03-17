CC ?= gcc
CXX ?= g++
CFLAGS ?= -O2
PREFIX ?= /usr/local
DESTDIR ?=
CFLAGS ?= -g 
CXXFLAGS ?= -g -DFUNC_LOGS
BUILD_DIR=./build

all:
	mkdir -p build
	$(CC) $(CFLAGS) -c src/tokenizer.c -o build/tokenizer.o
	$(CXX) $(CFLAGS) src/simplecalculator.cpp build/tokenizer.o -o build/calc
	
install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $(BUILD_DIR)/calc $(DESTDIR)$(PREFIX)/bin/
	cp $(BUILD_DIR)/functest $(DESTDIR)$(PREFIX)/bin/
./src/tokenizer/%.o: %.c:
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $<
clean:
	rm -rf build
