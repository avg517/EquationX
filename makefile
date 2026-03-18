CC ?= gcc
CXX ?= g++
CFLAGS ?= -O2
PREFIX ?= /usr/local
DESTDIR ?=
CFLAGS ?= -O2
TESTFLAGS ?= -g -O1
CXXFLAGS ?= -DFUNC_LOGS
BUILD_DIR=./build

OBJFILES := $(wildcard *.o)
CPPFILES := $(wildcard *.o)
CFILES := $(wildcard *.o)

all: $(OBJFILES)

	#$(CC) $(CFLAGS) -c src/tokenizer.c -o build/tokenizer.o
	$(CXX) $(CFLAGS) src/$(CPPFILES) build/$(OBJFILES) -o build/calc



$(OBJFILES):$(CFILES)
	mkdir -p build
	$(CC) $(CFLAGS) -c $(CFILES) -o build/$(OBJFILES)


install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $(BUILD_DIR)/calc $(DESTDIR)$(PREFIX)/bin/
	cp $(BUILD_DIR)/functest $(DESTDIR)$(PREFIX)/bin/
#./src/tokenizer/%.o: %.c:
#	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $<
clean:
	rm -rf build
