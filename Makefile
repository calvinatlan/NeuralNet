all: main

main: objects build main.o
	g++ -o build/neural-net objects/main.o

build:
	mkdir build

objects:
	mkdir objects

main.o:
	g++ -c src/main.cpp -o objects/main.o
