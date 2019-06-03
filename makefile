all: main

main: main.cpp Game.h
	g++ -std=c++11 -o main main.cpp Game.h -lncursesw

clean: rm -f main