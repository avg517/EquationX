CC ?= gcc
CXX ?= g++
#bro dont put it in usr/local...nixos doesnt take that lightly...
PREFIX ?=
DESTDIR ?=
CFLAGS ?=-O2 -c
CXXFLAGS ?= -g -DFUNC_LOGS
BUILD_DIR=./build
#hard coding the cpp files because of errors
SRC=./src/testfunctioncreation.cpp ./src/simplecalculator.cpp
#c files and their respective object file
CFILES=$(wildcard src/tokenizer/*.c) #searches cfiles in the src/tokenizer...if you wanna add a folder go ahead
OBJFILES = $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(notdir $(CFILES))))
#c++ output of compiled sourcefiles
outputfiles := $(patsubst ./src/%.cpp,$(BUILD_DIR)/%,$(SRC))
all: makefolder buildproject
	echo "Done"
makefolder:
	mkdir $(BUILD_DIR)
buildproject: $(OBJFILES) $(outputfiles)

$(BUILD_DIR)/%: src/%.cpp $(OBJFILES)
	$(CXX) $(OBJFILES) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/%.o: src/tokenizer/%.c
	$(CC) $(CFLAGS) $< -o $@
install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $(BUILD_DIR)/calc $(DESTDIR)$(PREFIX)/bin/
	cp $(BUILD_DIR)/functest $(DESTDIR)$(PREFIX)bin/
clean:
	rm -rf build
