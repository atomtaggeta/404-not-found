// game.cpp
#include "game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// (TEST ONLY)
const int RECTANGLE_WIDTH = 50;
const int RECTANGLE_HEIGHT = 50;

// (TEST ONLY)
Game::Game() : window(nullptr),renderer(nullptr),
rectX(SCREEN_WIDTH / 2 - RECTANGLE_WIDTH / 2),
rectY(SCREEN_HEIGHT / 2 - RECTANGLE_HEIGHT / 2) {

}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("SDL Rectangle Control", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void Game::run() {
    running = true;
    while (running) {
        input();
        update();
        render();
    }
}

void Game::input() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
    	// If quit is detected
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q))) {
            // Quit the game
            running = false;
            SDL_Quit();
            exit(0);

        // (TEST ONLY)
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_w:
                    rectY -= 5;
                    break;
                case SDLK_s:
                    rectY += 5;
                    break;
                case SDLK_a:
                    rectX -= 5;
                    break;
                case SDLK_d:
                    rectX += 5;
                    break;
            }
        }
    }
}

void Game::update() {
    // Update game state here (if needed)
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // (TEST ONLY)
    SDL_Rect rectangle = {rectX, rectY, RECTANGLE_WIDTH, RECTANGLE_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_RenderPresent(renderer);
}
