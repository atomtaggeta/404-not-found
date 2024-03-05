#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

class Player {
public:
    Player(SDL_Renderer* renderer, const int x, const int y, const float FPS, const int SW, const int SH);
    ~Player();

    void handle_input(SDL_Event event);
    void update();
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;

    const int FPS;
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    const int GROUND_LEVEL;

    const int WIDTH = 50;
    const int HEIGHT = 50;
    int direction = 0;
    float speed = FPS * 8.0;

    bool jumping = false;
    float jump_velocity = 0.0;
    const float jump_strength = FPS * 10.0;
    const float gravity = FPS * 0.25;

    void jump();
};

#endif // PLAYER_H
