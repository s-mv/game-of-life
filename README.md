# Conway's Game of Life
> by smv
## What is this?
The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970.  
Read more <a target="_blank" href="https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life">here</a>.  
I just made it in C++ for fun.
## How to play?
- run `main.linux x y` where `x` and `y` are optional as the grid dimensions.
- Holding space pauses the game while releasing it resumes. When held:
  - **click**/**drag** to _add cell(s)_
  - **shift** + **click**/**drag** to _remove tiles_
  - **right arrow key** to _move ahead by one frame_
## How to build?
### SFML
Make sure you have SFML (and make) set up, and then run
```bash
$ make sfml
```
or run the command
```bash
$ g++ ./src/main.sfml.cpp -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -o main.sfml
```
to build the file for your OS, and then run
```bash
$ ./main.sfml
```

### SDL2
Make sure you have SDL2 (and make) set up, and then run
```bash
$ make sdl
```
or run the command
```bash
$ g++ ./src/main.sdl.cpp -std=c++17 -o main.sdl
```
to build the file for your OS, and then run
```bash
$ ./main.sdl
```

## TODO
- Add in command for the user to set their own rules. The current rules are listed <a href="https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Rules">here</a>.