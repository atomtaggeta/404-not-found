#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

class Player {
public:
    Player(SDL_Renderer* renderer);
    ~Player();

    void movement(const Uint8* current_key_states);
    void update();
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;

    const int WIDTH = 50;
    const int HEIGHT = 50;
    int speed = 10;
    const int STARTING_X = 100;
    const int STARTING_Y = 1000;

    const int GROUND_LEVEL = 1000;
    bool jumping = false;
    int jump_count = 0;
    const int JUMP_HEIGHT = 100;

    void jump();
};

#endif // PLAYER_H
