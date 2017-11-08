CXX = g++
CXXFLAGS = -Wall -g

main: objects build main.o
	$(CXX) $(CXXFLAGS) -o build/neural-net objects/main.o

objects:
	mkdir objects

build:
	mkdir build

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o objects/main.o
