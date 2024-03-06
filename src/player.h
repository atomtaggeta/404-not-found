#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "textures.h"

enum Player_State {
    IDLE,
    RUN,
    JUMP_UP,
    JUMP_DOWN,
};

class Player {
public:
    Player(SDL_Renderer* renderer, struct Texture texture, const int x, const int y, const float FPS, const int SW, const int SH);
    ~Player();

    void handle_input(SDL_Event event);
    void update();
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;

    Player_State state = IDLE;

    const float FPS;
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    int GROUND_LEVEL;

    const int WIDTH = 240;
    const int HEIGHT = 160;
    int moving_direction = 0;
    float speed = FPS * 10.0;

    bool jumping = false;
    float jump_velocity = 0.0;
    const float jump_strength = FPS * 8.0;
    const float gravity = FPS * 0.25;

    struct Texture texture;
    int looking_direction = 1;

    void jump();
};

#endif // PLAYER_H
