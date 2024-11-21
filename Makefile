# CXX = g++
# CXXFLAGS = -std=c++17 -g -Wall -O2 -lncurses -lhunspell

# PROG ?= words
# OBJS = wordle.o  main.o 

# all: $(PROG)

# .cpp.o:
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<

# $(PROG): $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -lncurses

# clean:
# 	rm -rf $(EXEC) *.o *.out words

# rebuild: clean all

# run: all 
# 	./$(PROG)
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -O2 -I/usr/include/hunspell
LDFLAGS = -lncurses -lhunspell

PROG ?= words
OBJS = wordle.o main.o

all: $(PROG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(EXEC) *.o *.out words

rebuild: clean all

run: all
	./$(PROG)
