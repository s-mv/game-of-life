#pragma once

#include <SFML/Graphics.hpp>
#include <any>
#include <string>
#include <unordered_map>

class EventHandler {

private:
  sf::Event evt;
  sf::RenderWindow &window;

  void keyHandler(int code, bool pressed) {
    switch (code) {
    case sf::Keyboard::Space: {
      keys["space"] = pressed;
      break;
    }
    case sf::Keyboard::LShift:
    case sf::Keyboard::RShift: {
      keys["shift"] = pressed;
      break;
    }
    case sf::Keyboard::Right: {
      keys["right"] = pressed;
      break;
    }
    default: {
      break;
    }
    }
  }
  void mouseMoveHandler() {
    sf::Vector2i p = sf::Mouse::getPosition(window);
    mouse["x"] = p.x;
    mouse["y"] = p.y;
  }

public:
  std::unordered_map<std::string, bool> keys = {{"space", false},
                                                {"true", false}};
  std::unordered_map<std::string, int> mouse = {
      {"x", 0}, {"y", 0}, {"pressed", 0}};
  EventHandler(sf::RenderWindow &win) : window(win) {
    window.setFramerateLimit(42);
  }
  void run() {
    while (window.pollEvent(evt)) {
      switch (evt.type) {
      case sf::Event::Closed: {
        window.close(); // TODO: add a dialog box
        break;
      }
      case sf::Event::KeyPressed: {
        keyHandler(evt.key.code, true);
        break;
      }
      case sf::Event::KeyReleased: {
        keyHandler(evt.key.code, false);
        break;
      }
      case sf::Event::MouseButtonPressed: {
        mouse["pressed"] = 1;
        break;
      }
      case sf::Event::MouseButtonReleased: {
        mouse["pressed"] = 0;
        break;
      }
      case sf::Event::MouseMoved: {
        mouseMoveHandler();
      }
      default: {
        break;
      }
      }
    }
  }
};