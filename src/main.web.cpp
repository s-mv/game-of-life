/* name:   conway's game of life
   author: smv */

#include <cmath>
#include <string>

#include <SDL2/SDL.h>

#include "./conway.hpp"
#include "./eventhandler.sdl.hpp"

#include <emscripten.h>

int width = 30, height = 30;
int winwid = 600, winhgt = 600;
int state = 1; // 0 for pause, 1 for resume

float i = 0;
// handling time
uint64_t NOW = SDL_GetPerformanceCounter();
uint64_t LAST = 0;
double deltaTime = 0;
std::vector<std::string> rules = {};
std::vector<std::vector<int>> life;

SDL_Window *window;
SDL_Renderer *renderer;
EventHandler handler = NULL;

// thanks a lot https://github.com/timhutton/sdl-canvas-wasm/

void mainLoop(void) {
  LAST = NOW;
  NOW = SDL_GetPerformanceCounter();
  deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
  i += deltaTime;

  handler.run();

  if (handler.keys["esc"]) {
    emscripten_run_script("document.querySelector(\".container\").classList.add(\"hidden\");");
    emscripten_cancel_main_loop();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    exit(0);
  }

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

  SDL_SetRenderDrawColor(renderer, 0xff, 0xba, 0x37, 0xff);
  SDL_RenderClear(renderer);

  for (std::vector<int>::size_type y = 0; y < life.size(); y++) {
    for (std::vector<int>::size_type x = 0; x < life[y].size(); x++) {
      if (life[y][x] != 0) {
        int x_ = x * winwid / width;
        int y_ = y * winhgt / height;
        SDL_Rect rect;
        rect.x = x_, rect.y = y_, rect.w = winwid / width,
        rect.h = winhgt / height;
        SDL_SetRenderDrawColor(renderer, 0x53, 0x00, 0xc6, 0xff);
        SDL_RenderFillRect(renderer, &rect);
      }
    }
  }
  SDL_RenderPresent(renderer);
}

int main(int argc, char **argv) {
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

  for (int i = 0; i < rules.size(); i++)
    // setting up dimensions
    if (width > height) {
      winhgt = winwid * height / width;
    } else if (width < height) {
      winwid = winhgt * width / height;
    }
  life.assign(height, std::vector<int>(width, 0));

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }

  SDL_CreateWindowAndRenderer(winwid, winhgt, 0, &window, &renderer);

  SDL_Event e;

  handler = EventHandler(window);

  const int simulate_infinite_loop = 1;
  const int fps = -1;

  emscripten_set_main_loop(mainLoop, 60, 1);

  return 0;
}
