CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LIBS = -lglfw -lGL -lGLEW

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main $(LIBS)

clean:
	rm -fr main
