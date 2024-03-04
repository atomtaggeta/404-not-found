#include "player.h"

Player::Player(SDL_Renderer* renderer, int x, int y, const int SW, const int SH) : renderer(renderer), GROUND_LEVEL(y), SCREEN_WIDTH(SW), SCREEN_HEIGHT(SH) {
    rect.x = x;
    rect.y = y;
    rect.w = WIDTH;
    rect.h = HEIGHT;
}

Player::~Player() {
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
            case SDLK_w:
                if (!jumping) {
                    jumping = true;
                    jump_velocity = -jump_strength;
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
    rect.x += direction * speed;

    // Ensure player stays within the screen boundaries
    if (rect.x < 0) {
        rect.x = 0;
    } else if (rect.x > SCREEN_WIDTH - WIDTH) {
        rect.x = SCREEN_WIDTH - WIDTH;
    }

    // Control the jump of the player
    rect.y += jump_velocity;
    jump_velocity += gravity;

    if (rect.y > GROUND_LEVEL) {
        rect.y = GROUND_LEVEL;
        jump_velocity = 0;
        jumping = false;
    }

}

void Player::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
