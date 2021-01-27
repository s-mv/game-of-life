#pragma once

#include <SDL2/SDL.h>
#include <any>
#include <string>
#include <unordered_map>

class EventHandler {
private:
  SDL_Event e;
  SDL_Window *window;
  // resizing the window, need to set more things up
  void keyHandler(int code, bool pressed) {
    switch (code) {
    case SDLK_SPACE: {
      keys["space"] = pressed;
      break;
    }
    case SDLK_LSHIFT:
    case SDLK_RSHIFT: {
      keys["shift"] = pressed;
      break;
    }
    case SDLK_RIGHT: {
      keys["right"] = pressed;
      break;
    }
    default: {
      break;
    }
    }
  }
  void mouseMoveHandler() { SDL_GetMouseState(&mouse["x"], &mouse["y"]); }

public:
  bool quit = false;
  std::unordered_map<std::string, bool> keys = {{"space", false},
                                                {"true", false}};
  std::unordered_map<std::string, int> mouse = {
      {"x", 0}, {"y", 0}, {"pressed", 0}};
  EventHandler(SDL_Window *window) : window(window) {}
  void run() {
    while (SDL_PollEvent(&e) != 0) {
      switch (e.type) {
      case SDL_QUIT: {
        quit = true;
        break;
      }
      case SDL_KEYDOWN: {
        keyHandler(e.key.keysym.sym, true);
        break;
      }

      case SDL_KEYUP: {
        keyHandler(e.key.keysym.sym, false);
        break;
      }
      case SDL_MOUSEBUTTONDOWN: {
        mouse["pressed"] = 1;
        break;
      }
      case SDL_MOUSEBUTTONUP: {
        mouse["pressed"] = 0;
        break;
      }
      case SDL_MOUSEMOTION: {
        mouseMoveHandler();
      }
      default:
        break;
      }
    }
  }
};