CFLAGS ?= -O0
CXXFLAGS ?= -O0

test:graph_generator.cpp test.cpp
	g++ $(CXXFLAGS) -g ../tokenizer/tokens.h graph_generator.cpp test.cpp   -o test

clean:
	rm test