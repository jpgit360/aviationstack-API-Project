CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -fopenmp -g
LIBS := -ljsoncpp

SRC_FILES := main.cpp aviation_data.cpp trie.cpp
OBJECTS := $(SRC_FILES:.cpp=.o)
EXECUTABLE := output

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)