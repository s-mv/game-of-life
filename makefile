SFMLFLAGS= -lsfml-graphics -lsfml-window -lsfml-system
SDLFLAGS= -lSDL2
sfml:
	g++ ./src/main.sfml.cpp -std=c++17 $(SFMLFLAGS) -o main.sfml
sdl:
	g++ ./src/main.sdl.cpp -std=c++17 $(SDLFLAGS) -o main.sdl