main.exe: main.o vec3.o
	g++ -Wall -o main.exe main.o vec3.o
main.o: main.cpp
	g++ -Wall -c main.cpp
vec3.o: vec3.cpp
	g++ -Wall -c vec3.cpp