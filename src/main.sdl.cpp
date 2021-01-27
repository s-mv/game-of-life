/* name:   conway's game of life
   author: smv */

#include <cmath>

#include <SDL2/SDL.h>

#include "./conway.hpp"
#include "./eventhandler.sdl.hpp"

int width = 30, height = 30;

int winwid = 600, winhgt = 600;

int state = 1; // 0 for pause, 1 for resume

int main(int argc, char **argv) {
  // check if dimensions are provided
  // TODO: resize/scale stuff according to dimensions
  (argv[1] && argv[2]) &&
      (width = std::atoi(argv[1]), height = std::atoi(argv[2]));
  if (width > height) {
    winhgt = winwid * height / width;
  } else if (width < height) {
    winwid = winhgt * width / height;
  }
  std::vector<std::vector<int>> life(height, std::vector<int>(width, 0));

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
  SDL_Window *window =
      SDL_CreateWindow("conway", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       winwid, winhgt, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }
  SDL_Surface *surface = SDL_GetWindowSurface(window);
  SDL_Event e;
  SDL_UpdateWindowSurface(window);
  SDL_Delay(2000);

  EventHandler handler = EventHandler(window);

  float i = 0;
  // handling time
  uint64_t NOW = SDL_GetPerformanceCounter();
  uint64_t LAST = 0;
  double deltaTime = 0;

  while (!handler.quit) {
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
    i += deltaTime;

    handler.run();
    state = (int)!handler.keys["space"];

    if (handler.mouse["pressed"] != 0 && state == 0) {
      life[floor(handler.mouse["y"] * height / winhgt)]
          [floor(handler.mouse["x"] * width / winwid)] =
              (int)!handler.keys["shift"];
    }

    if (state == 1 && i >= 0.25) {
      conways(life);
      i = 0;
    } else if (state == 0 && handler.keys["right"] && i >= 0.1) {
      conways(life);
      i = 0;
    }
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xff, 0xba, 0x37));
    for (std::vector<int>::size_type y = 0; y < life.size(); y++) {
      for (std::vector<int>::size_type x = 0; x < life[y].size(); x++) {
        if (life[y][x] != 0) {
          int x_ = x * winwid / width;
          int y_ = y * winhgt / height;
          SDL_Rect rect = {x_, y_, winwid / width, winhgt / height};
          SDL_FillRect(surface, &rect,
                       SDL_MapRGB(surface->format, 0x53, 0x00, 0xc6));
        }
      }
    }
    SDL_UpdateWindowSurface(window);
  }
  SDL_FreeSurface(surface);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}