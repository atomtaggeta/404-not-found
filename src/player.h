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
    float speed = 7.5;

    bool jumping = false;
    float jump_velocity = 0.0;
    const float jump_strength = 7.5;
    const float gravity = 0.2;

    void jump();
};

#endif // PLAYER_H
