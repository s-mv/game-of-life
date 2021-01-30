/* name:   conway's game of life
   author: smv */

#include <cmath>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "./conway.hpp"
#include "./eventhandler.sfml.hpp"

int width = 30, height = 30;

int winwid = 600, winhgt = 600;

int state = 1; // 0 for pause, 1 for resume

int main(int argc, char **argv) {
  std::vector<std::string> rules = {};
  for (size_t i = 0; i < argc; i++) {
    // check if dimensions are provided
    if (std::string(argv[i]) == "-d") {
      argv[i + 1] && (width = std::atoi(argv[i + 1]));
      argv[i + 2] && (height = std::atoi(argv[i + 2]));
    };
    // check for rules
    if (std::string(argv[i]) == "-r") {
      size_t n = i + 1;
      while (true) {
        if (n >= argc || std::string(argv[n]) == ";")
          break;
        rules.push_back(std::string(argv[n++]));
      }
    }
  }
  // setting up dimensions
  if (width > height) {
    winhgt = winwid * height / width;
  } else if (width < height) {
    winwid = winhgt * width / height;
  }

  std::vector<std::vector<int>> life(height, std::vector<int>(width, 0));

  sf::RenderWindow window(sf::VideoMode(winwid, winhgt), "My window",
                          sf::Style::Default);

  window.setVerticalSyncEnabled(true);
  EventHandler handler = EventHandler(window);

  sf::Clock clock;
  float i = 0;
  while (window.isOpen()) {
    sf::Time elapsed = clock.restart();
    i += elapsed.asSeconds();
    window.clear(sf::Color(0xefaa27ff));

    handler.run();
    state = (int)!handler.keys["space"];

    if (handler.mouse["pressed"] != 0 && state == 0) {
      life[handler.mouse["y"] * height / winhgt % height]
          [handler.mouse["x"] * width / winwid % width] =
              (int)!handler.keys["shift"];
    }

    if (state == 1 && i >= 0.25) {
      conways(life, rules);
      i = 0;
    } else if (state == 0 && handler.keys["right"] && i >= 0.1) {
      conways(life, rules);
      i = 0;
    }
    for (std::vector<int>::size_type y = 0; y < life.size(); y++) {
      for (std::vector<int>::size_type x = 0; x < life[y].size(); x++) {
        if ((life[y][x] != 0)) {
          sf::RectangleShape rect(
              sf::Vector2f(winwid / width, winhgt / height));
          rect.setFillColor(sf ::Color(0x5300c6ff));
          rect.setPosition((winwid + x * winwid) / width,
                           (winhgt + y * winhgt) / height);
          window.draw(rect);
        }
      }
    }
    window.display();
  }
  return 0;
}
