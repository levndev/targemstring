all:
	g++ -g -std=c++11 String.h String.cpp tests.h main.cpp -o main
debug:
	g++ -g -std=c++11 String.h String.cpp tests.h main.cpp -o main -D DEBUG