// game.h
#pragma once

#include <SDL2/SDL.h>

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    void input();
    void update();
    void render();

    bool running = false;

    // (TEST ONLY)
    int rectX;
    int rectY;
};
