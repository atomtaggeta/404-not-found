#include "player.h"


Player::Player(SDL_Renderer* renderer, struct Texture texture, int x, int y, const float FPS, const int SW, const int SH):
renderer(renderer), texture(texture), FPS(FPS), SCREEN_WIDTH(SW), SCREEN_HEIGHT(SH) {
    GROUND_LEVEL = y - HEIGHT;
    rect.x = x;
    rect.y = y - HEIGHT;
    rect.w = WIDTH;
    rect.h = HEIGHT;
}

Player::~Player() {
}

void Player::handle_input(SDL_Event event) {
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_a:
                moving_direction = -1;
                break;
            case SDLK_d:
                moving_direction = 1;
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
                if (moving_direction == -1) {
                    moving_direction = 0;
                }
                break;
            case SDLK_d:
                if (moving_direction == 1) {
                    moving_direction = 0;
                }
                break;
        }
    }
}

void Player::update() {
    // If there is a moving direction
    if (moving_direction) {
        // Move the player left and right
        rect.x += moving_direction * speed / FPS;

        // Set the state to run
        state = RUN;
    }
    // If there is no moving direction
    else {
        // Set the state to idle
        state = IDLE;
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

    // Bound the player to the gound
    if (rect.y > GROUND_LEVEL) {
        rect.y = GROUND_LEVEL;
        jump_velocity = 0;
        jumping = false;
    }

    // So velocity doesnt get bigger over time
    if (!jumping) {
        jump_velocity = 0;
    }

    // If enough time has passed between frames, switch to the next frame
    if ((SDL_GetTicks() - texture.frame_start) > (FPS / texture.render_speed)) {
        texture.current_frame = (texture.current_frame + 1) % texture.num_of_frames;
        texture.frame_start = SDL_GetTicks();
    }

    // Set the looking direction
    if (moving_direction) {
        looking_direction = moving_direction;
    }
}

void Player::render() {
    // Flip the texture depending on the looking direction
    SDL_RendererFlip flip = (looking_direction == 1) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

    // Set the rendering texture according to the players state
    SDL_Texture* render_texture;
    SDL_Rect* render_rect;
    if (state == IDLE) {
        render_texture = texture.idle.texture;
        render_rect = &texture.idle.frame_rects[texture.current_frame];
    }
    else if (state == RUN) {
        render_texture = texture.run.texture;
        render_rect = &texture.run.frame_rects[texture.current_frame];
    }

    // Render the current frame
    SDL_RenderCopyEx(renderer, render_texture, render_rect, &rect, 0, nullptr, flip);
    
    //SDL_RenderCopy(renderer, texture.texture, &texture.idle.frame_rects[texture.current_frame], &rect);
}
