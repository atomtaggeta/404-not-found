#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

class Player {
public:
    Player(SDL_Renderer* renderer, const int x, const int y, const int SW, const int SH);
    ~Player();

    void handle_input(SDL_Event event);
    void update();
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;

    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    const int GROUND_LEVEL;

    const int WIDTH = 50;
    const int HEIGHT = 50;
    int direction = 0;
    float speed = 1.0f;

    bool jumping = false;
    float jump_velocity = 0.0f;
    float jump_strength = 2.5f;
    float gravity = 0.01f;

    void jump();
};

#endif // PLAYER_H
