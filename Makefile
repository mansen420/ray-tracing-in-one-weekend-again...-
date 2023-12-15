DEPS := $(wildcard include/*.h)
all: build/main.exe
	./build/main.exe

build/main.exe: build/main.o build/vec3.o build/geometry.o build/material.o
	g++ -Wall -o build/main.exe build/main.o build/vec3.o build/geometry.o build/material.o

build/main.o: src/main.cpp $(DEPS)
	g++ -Wall -c -o build/main.o src/main.cpp

build/vec3.o: src/vec3.cpp $(DEPS)
	g++ -Wall -c -o build/vec3.o src/vec3.cpp

build/geometry.o: src/geometry.cpp $(DEPS)
	g++ -Wall -c -o build/geometry.o src/geometry.cpp

build/material.o: src/material.cpp $(DEPS)
	g++ -Wall -c -o build/material.o src/material.cpp

clean:
	rm *.o *.log