main.exe: main.o vec3.o 
	g++ -Wall -o main.exe main.o vec3.o
main.o: main.cpp global_constants.h vec3.h ray.h
	g++ -Wall -c main.cpp
vec3.o: vec3.cpp vec3.h
	g++ -Wall -c vec3.cpp