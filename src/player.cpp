#include "player.h"


Player::Player(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, const float FPS, const int SW, const int SH):
renderer(renderer), texture(texture), FPS(FPS), SCREEN_WIDTH(SW), SCREEN_HEIGHT(SH) {
    GROUND_LEVEL = y - HEIGHT;
    rect.x = x;
    rect.y = y - HEIGHT;
    rect.w = WIDTH;
    rect.h = HEIGHT;

    frame_rects = new SDL_Rect[NUM_FRAMES];

    for (int i = 0; i < NUM_FRAMES; i++) {
        frame_rects[i].x = i * FRAME_WIDTH;
        frame_rects[i].y = 0;
        frame_rects[i].w = FRAME_WIDTH;
        frame_rects[i].h = FRAME_HEIGHT;
    }

    frame_start = SDL_GetTicks();
}

Player::~Player() {
    delete frame_rects;
}

void Player::handle_input(SDL_Event event) {
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_a:
                direction = -1;
                break;
            case SDLK_d:
                direction = 1;
                break;
            case SDLK_SPACE:
                if (!jumping) {
                    jumping = true;
                    jump_velocity = -jump_strength / FPS;
                }
                break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_a:
                if (direction == -1) {
                    direction = 0;
                }
                break;
            case SDLK_d:
                if (direction == 1) {
                    direction = 0;
                }
                break;
        }
    }
}

void Player::update() {
    // Move the player left and right
    if (direction) {
        rect.x += direction * speed / FPS;
    }

    // Ensure player stays within the screen boundaries
    if (rect.x < 0) {
        rect.x = 0;
    } else if (rect.x > SCREEN_WIDTH - WIDTH) {
        rect.x = SCREEN_WIDTH - WIDTH;
    }

    // Control the jump of the player
    if (jumping) {
        rect.y += jump_velocity;
        jump_velocity += gravity / FPS;
    }

    if (rect.y > GROUND_LEVEL) {
        rect.y = GROUND_LEVEL;
        jump_velocity = 0;
        jumping = false;
    }

    if (!jumping) {
        jump_velocity = 0;
    }

    if ((SDL_GetTicks() - frame_start) > (FPS / 3.0)) {
        current_frame = (current_frame + 1) % NUM_FRAMES;
        frame_start = SDL_GetTicks();
    }
}

void Player::render() {
    SDL_RenderCopy(renderer, texture, &frame_rects[current_frame], &rect);
}
