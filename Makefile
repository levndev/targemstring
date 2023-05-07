all:
	g++ -g -std=c++11 String.h String.cpp main.cpp -o main
debug:
	g++ -g -std=c++11 String.h String.cpp main.cpp -o main -D DEBUG