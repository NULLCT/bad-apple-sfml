main: main.cpp
	clang++ -std=c++17 -I/usr/local/include -lsfml-graphics -lsfml-window -lsfml-system main.cpp
