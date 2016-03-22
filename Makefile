CXX = g++
CSSFLAGS = -std=c++11 -Wall -g

test: test.o Vector.o
	$(CXX) $(CSSFLAGS) -o test test.o Vector.o Matrix.o
test.o: test.cpp Vector.h
	$(CXX) $(CSSFLAGS) -c test.cpp
Vector.o: Vector.h
	$(CXX) $(CSSFLAGS) -c Vector.cpp
Matrix.o: Matrix.h
	$(CXX) $(CSSFLAGS) -c Matrix.cpp