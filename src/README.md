# Conway's Game of Life
> by smv
## What is this?
The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970.  
Read more <a target="_blank" href="https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life">here</a>.  
I just made it in C++ for fun. As you can see, `main.linux` is already built for you.
## How to play?
- run `main.linux (x) (y)` where `x` and `y` are optional as the grid dimensions.
- Holding space pauses the game while releasing it resumes. When held:
  - **click**/**drag** to _add cell(s)_
  - **shift** + **click**/**drag** to _remove tiles_
  - **right arrow key** to _move ahead by one frame_
## How to build?
Make sure you have SFML (and make) set up, and then run
```bash
$ make
```
or run the command
```bash
$ g++ ./main.cpp -std=c++17 -lSDL2 -o main
```
to build the file for your OS.

## TODO
- Add in command for the user to set their own rules. The current rules are listed <a href="https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Rules">here</a>.
- Move from SFML to SDL for fun :P