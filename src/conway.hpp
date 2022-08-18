#pragma once

#include <vector>

std::vector<std::vector<int>> conways(std::vector<std::vector<int>> &npt,
                                      std::vector<std::string> rules) {
  std::vector<std::vector<int>> neu = npt;
  for (std::vector<int>::size_type y = 0; y < npt.size(); y++) {
    /* 1. Any live cell with fewer than two live neighbours dies, as if by
       underpopulation.
       2. Any live cell with two or three live neighbours lives on to the next
       generation.
       3. Any live cell with more than three live neighbours dies, as if by
       overpopulation.
       4. Any dead cell with exactly three live neighbours becomes a live cell,
       as if by reproduction.
       - source: Wikipedia    */
    for (std::vector<int>::size_type x = 0; x < npt[y].size(); x++) {
      // conditionals to check for edges
      int neighbours =
          // top left
          ((x > 0 && y > 0) && neu.at(y - 1).at(x - 1)) +
          // top middle
          ((y > 0) && neu.at(y - 1).at(x)) +
          // top right
          ((x < neu[y].size() - 1 && y > 0) && neu.at(y - 1).at(x + 1)) +
          // center left
          ((x > 0) && neu.at(y).at(x - 1)) +
          // center right
          // (no center middle, as center middle is the cell we are at)
          ((x < neu[y].size() - 1) && neu.at(y).at(x + 1)) +
          // bottom left
          ((x > 0 && y < neu.size() - 1) && neu.at(y + 1).at(x - 1)) +
          // bottom middle
          ((y < neu.size() - 1) && neu.at(y + 1).at(x)) +
          // bottom right
          ((x < neu[y].size() - 1 && y < neu.size() - 1) &&
           neu.at(y + 1).at(x + 1));
      if (rules.size() > 0) {
        // example syntax: "-r m3=1 l2=1 e4=0 ;"
        for (size_t i = 0; i < rules.size(); i++) {
          if (std::string(1, rules[i].at(0)) == "l") {
            (neighbours < (int)rules[i].at(1) - '0') &&
                (npt[y][x] = (int)rules[i].at(3) - '0');
          } else if (std::string(1, rules[i].at(0)) == "m") {
            (neighbours > (int)rules[i].at(1) - '0') &&
                (npt[y][x] = (int)rules[i].at(3) - '0');
          } else {
            (neighbours == (int)rules[i].at(1) - '0') &&
                (npt[y][x] = (int)rules[i].at(3) - '0');
          }
        }
      } else {
        // rule 2 can be skipped in the logic loops
        // rules 1 and 3
        (neighbours < 2 || neighbours > 3) && (npt[y][x] = 0);
        // rule 4
        (neighbours == 3) && (npt[y][x] = 1);
      }
    }
  }
  return npt;
}
