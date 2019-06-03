all: main

main: main.cpp Game.h Character.h Define.h
	g++ -std=c++11 -o main main.cpp Game.h Character.h Define.h -lncursesw

clean: rm -f main