#include "player.h"

Player::Player(SDL_Renderer* renderer) : renderer(renderer) {
    rect.x = STARTING_X;
    rect.y = STARTING_Y;
    rect.w = WIDTH;
    rect.h = HEIGHT;
}

Player::~Player() {
}

void Player::movement(const Uint8* current_key_states) {
	if (current_key_states[SDL_SCANCODE_LEFT]) {
        rect.x -= speed;
    }
    if (current_key_states[SDL_SCANCODE_RIGHT]) {
        rect.x += speed;
    }
    if (current_key_states[SDL_SCANCODE_UP]) {
        jump();
    }
}

void Player::update() {
	if (jumping) {
        if (jump_count < JUMP_HEIGHT) {
            rect.y -= 1;
            jump_count += 1;
        } else {
            jumping = false;
            jump_count = 0;
        }
    }
    else if (rect.y < GROUND_LEVEL) {
        rect.y += 1;
    }

}

void Player::jump() {
	if (!jumping && rect.y == GROUND_LEVEL) {
        jumping = true;
    }
}

void Player::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
