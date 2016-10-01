CXX	 = /usr/bin/g++
CXXFLAGS = -std=c++11
BIN	 = hashmap_test

SRCS	 = $(wildcard *.cpp)
OBJS	 = $(SRCS:%.cpp=%.o)

all: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BIN) $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f *.o *~ *#
	rm $(BIN)

