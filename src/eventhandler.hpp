#pragma once

#include <SFML/Graphics.hpp>
#include <any>
#include <string>
#include <unordered_map>

// I did a bit mistake using this, I don't like throwing away 'em scopes
// TODO: remove these
using namespace sf;
using namespace std;

class EventHandler {

private:
  sf::Event evt;
  sf::RenderWindow &window;
  const sf::Vector2u designedsize;
  // resizing the window, need to set more things up
  void resize(const Vector2u designedsize) {
    FloatRect viewport(0.f, 0.f, 1.f, 1.f);

    float screenwidth = evt.size.width / static_cast<float>(designedsize.x);
    float screenheight = evt.size.height / static_cast<float>(designedsize.y);

    if (screenwidth > screenheight) {
      viewport.width = screenheight / screenwidth;
      viewport.left = (1.f - viewport.width) / 2.f;
    } else if (screenwidth < screenheight) {
      viewport.height = screenwidth / screenheight;
      viewport.top = (1.f - viewport.height) / 2.f;
    }

    View view(FloatRect(0, 0, designedsize.x, designedsize.y));
    view.setViewport(viewport);
    window.setView(view);
  }
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
    Vector2i p = Mouse::getPosition(window);
    mouse["x"] = p.x;
    mouse["y"] = p.y;
  }

public:
  std::unordered_map<string, bool> keys = {{"space", false}, {"true", false}};
  std::unordered_map<string, int> mouse = {{"x", 0}, {"y", 0}, {"pressed", 0}};
  EventHandler(sf::RenderWindow &win)
      : window(win), designedsize(win.getSize().x, win.getSize().y) {
    window.setFramerateLimit(42);
  }
  void run() {
    while (window.pollEvent(evt)) {
      switch (evt.type) {
      case Event::Closed: {
        window.close(); // TODO: add a dialog box
        break;
      }
      case Event::KeyPressed: {
        keyHandler(evt.key.code, true);
        break;
      }
      case Event::KeyReleased: {
        keyHandler(evt.key.code, false);
        break;
      }
      case Event::Resized: {
        resize(designedsize);
        break;
      }
      case Event::MouseButtonPressed: {
        mouse["pressed"] = 1;
        break;
      }
      case Event::MouseButtonReleased: {
        mouse["pressed"] = 0;
        break;
      }
      case Event::MouseMoved: {
        mouseMoveHandler();
      }
      default: {
        break;
      }
      }
    }
  }
};