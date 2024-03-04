#include "game.h"

// (TEST ONLY)
Game::Game() {
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Get the display mode of the primary monitor
    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
        // Handle getting display mode error
        printf("SDL could not get display dimensions! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create the windows using the monitors dimensions (fullscreen)
    window = SDL_CreateWindow("Dante's Resurrection", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayMode.w, displayMode.h, SDL_WINDOW_FULLSCREEN);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Disable the cursor
    SDL_ShowCursor(SDL_DISABLE);

    // Initialize the player object (with starting position)
    player = new Player(renderer, 100, displayMode.h - 100, displayMode.w, displayMode.h);

    return true;
}

void Game::run() {
    while (running) {
        input();
        update();
        render();
    }
}

void Game::input() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
    	// If quit is detected
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q))) {
            // Quit the game
            running = false;
            SDL_Quit();
            exit(0);
        }

        // Handle the input for the player
        player->handle_input(event);
    }
}

void Game::update() {
    // Update the player
    player->update();
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0x0);
    SDL_RenderClear(renderer);

    // Render the player object
    player->render();

    SDL_RenderPresent(renderer);
}
