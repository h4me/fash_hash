CC=g++ -std=c++0x -Wall -g -I./3party/include


main: main.cpp
	$(CC) -o prog main.cpp -L ./3party/lib -lfmt




