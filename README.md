# Conway's Game of Life
> by smv
## What is this?
The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970.  
Read more <a target="_blank" href="https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life">here</a>.  
I just made it in C for fun.
Web version <a target="_blank" href="https://s-mv.github.io/game-of-life/">here</a>.
## How to play?
### Controls
- Holding space pauses the game while releasing it resumes. When held:
  - **click**/**drag** to _add cell(s)_
  - **shift** + **click**/**drag** to _remove tiles_
  - **right arrow key** to _move ahead by one frame_

### Custom rules
Pressing **shift** will toggle the rules bar.  
The _rules_ can be something like `l3=0 m4=1 =6=0` for example
- `l` means less than, `r` means more than and `=` means, well, equal to.
- The number just after defines the number of cells.
- The number at the end defines if a cell should be alive or dead if true.
So `l3=0` translates to `if less than 3 neighbours, cell should be dead`

## How to build?
```bash
make build
```
**Run** using
```
npm run dev
```

Or serve `.` using a web server of your choice.
Or try the web version directly <a target="_blank" href="https://s-mv.github.io/game-of-life/">here</a> :P
