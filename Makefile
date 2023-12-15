main.exe: main.o vec3.o geometry.o
	g++ -Wall -o main.exe main.o vec3.o geometry.o
main.o: main.cpp global_constants.h geometry.h ray.h
	g++ -Wall -c main.cpp
vec3.o: vec3.cpp vec3.h
	g++ -Wall -c vec3.cpp
geometry.o: geometry.cpp geometry.h ray.h vec3.h
	g++ -Wall -c geometry.cpp