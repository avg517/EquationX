#this is the second version of the makefile which is WIP
CC ?= gcc
CXX ?= g++
CFLAGS ?= -O2
PREFIX ?= /usr/local
DESTDIR ?=
CFLAGS ?= -O2
TESTFLAGS ?= -g -O1
CXXFLAGS ?= -DFUNC_LOGS
BUILD_DIR=./build

OBJFILES := $(wildcard *.c.o)
CPPFILES := $(wildcard *.cpp)
HFILES ?= $(wildcard *.h)
HPPFILES ?= $(wildcard *.hpp)
CFILES := $(wildcard *.c)

all: $(CFILES) $(CPPFILES)

	$(CC) $(CFLAGS) -c src/$(CFILES) src/$(HFILES) -o build/$(CFILES).o
	$(CXX) $(CFLAGS) src/$(CPPFILES) src/$(HPPFILES) build/$(OBJFILES) -o build/calc

clean:
	rm -rf build
	rm -r $(OBJFILES)
