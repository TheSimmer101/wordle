CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -O2 -lncurses

PROG ?= words
OBJS = wordle.o  main.o 

all: $(PROG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -lncurses

clean:
	rm -rf $(EXEC) *.o *.out words

rebuild: clean all

run: all 
	./$(PROG)