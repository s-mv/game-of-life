CXXFLAGS= -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system
out:
	g++ ./src/main.cpp $(CXXFLAGS) -o main
clean:
	rm *.o