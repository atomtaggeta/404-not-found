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
                direction_X = -1;
                break;
            case SDLK_d:
                direction_X = 1;
                break;
            case SDLK_w:
                if (jump_count < 2) {
                    jumping = true;
                    jump_count++;
                    vel_Y = -jump_strength / FPS;
                }
                break;
            case SDLK_0:
                state = ATTACK;
                break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_a:
                if (direction_X == -1) {
                    direction_X = 0;
                }
                break;
            case SDLK_d:
                if (direction_X == 1) {
                    direction_X = 0;
                }
                break;
            case SDLK_0:
                state = IDLE;
                break;
        }
    }
}

void Player::update() {
    // If there is a X moving direction
    if (direction_X) {
        // Move the player left and right
        rect.x += direction_X * speed / FPS;
    }

    // Ensure player stays within the screen boundaries
    if (rect.x < 0) {
        rect.x = 0;
    } else if (rect.x > SCREEN_WIDTH - WIDTH) {
        rect.x = SCREEN_WIDTH - WIDTH;
    }

    // Control the jump of the player
    if (jumping) {
        rect.y += vel_Y;
        vel_Y += gravity / FPS;
    }

    // Bound the player to the gound
    if (rect.y > GROUND_LEVEL) {
        rect.y = GROUND_LEVEL;
        vel_Y = 0;
        jumping = false;
        jump_count = 0;
    }

    // So Y velocity doesnt get bigger over time
    if (!jumping) {
        vel_Y = 0;
    }

    // Set the player states other than attack
    if (state != ATTACK) {
        if (vel_Y < 0) {
            state = JUMP_UP;
        }
        else if (vel_Y > 0) {
            state = JUMP_DOWN;
        }
        else if (direction_X) {
            state = RUN;
        }
        else {
            state = IDLE;
        }
    }


    // TEST ONLY
    if (state == IDLE) {
        printf("IDLE\n");
    }
    else if (state == RUN) {
        printf("RUN\n");
    }
    else if (state == ATTACK) {
        printf("ATTACK\n");
    }
    else if (state == JUMP_UP) {
        printf("JUMP_UP\n");
    }
    else if (state == JUMP_DOWN) {
        printf("JUMP_DOWN\n");
    }


    // Set the looking direction
    if (direction_X) {
        looking_direction = direction_X;
    }

    // Get the last frames start time and the render speed it should have
    Uint32 frame_start;
    float render_speed;
    if (state == IDLE) {
        frame_start = texture.idle.frame_start;
        render_speed = texture.idle.render_speed;
    }
    else if (state == RUN) {
        frame_start = texture.run.frame_start;
        render_speed = texture.run.render_speed;
    }
    else if (state == JUMP_UP) {
        frame_start = texture.jump_up.frame_start;
        render_speed = texture.jump_up.render_speed;
    }
    else if (state == JUMP_DOWN) {
        frame_start = texture.jump_down.frame_start;
        render_speed = texture.jump_down.render_speed;
    }
    else if (state == ATTACK) {
        frame_start = texture.attack.frame_start;
        render_speed = texture.attack.render_speed;
    }

    // If enough time has passed between frames
    if ((SDL_GetTicks() - frame_start) > (FPS / render_speed)) {
        // Update the specific state animations current frame and update frame start time
        if (state == IDLE) {
            texture.idle.current_frame = (texture.idle.current_frame + 1) % texture.idle.num_of_frames;
            texture.idle.frame_start = SDL_GetTicks();
        }
        else if (state == RUN) {
            texture.run.current_frame = (texture.run.current_frame + 1) % texture.run.num_of_frames;
            texture.run.frame_start = SDL_GetTicks();
        }
        else if (state == JUMP_UP) {
            texture.jump_up.current_frame = (texture.jump_up.current_frame + 1) % texture.jump_up.num_of_frames;
            texture.jump_up.frame_start = SDL_GetTicks();
        }
        else if (state == JUMP_DOWN) {
            texture.jump_down.current_frame = (texture.jump_down.current_frame + 1) % texture.jump_down.num_of_frames;
            texture.jump_down.frame_start = SDL_GetTicks();
        }
        else if (state == ATTACK) {
            texture.attack.current_frame = (texture.attack.current_frame + 1) % texture.attack.num_of_frames;
            texture.attack.frame_start = SDL_GetTicks();
        }
        
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
        render_rect = &texture.idle.frame_rects[texture.idle.current_frame];
    }
    else if (state == RUN) {
        render_texture = texture.run.texture;
        render_rect = &texture.run.frame_rects[texture.run.current_frame];
    }
    else if (state == JUMP_UP) {
        render_texture = texture.jump_up.texture;
        render_rect = &texture.jump_up.frame_rects[texture.jump_up.current_frame];
    }
    else if (state == JUMP_DOWN) {
        render_texture = texture.jump_down.texture;
        render_rect = &texture.jump_down.frame_rects[texture.jump_down.current_frame];
    }
    else if (state == ATTACK) {
        render_texture = texture.attack.texture;
        render_rect = &texture.attack.frame_rects[texture.attack.current_frame];
    }

    // Render the current frame
    SDL_RenderCopyEx(renderer, render_texture, render_rect, &rect, 0, nullptr, flip);

    // TEST FOR HITBOXES
    SDL_RenderDrawRect(renderer, &rect);
    
    //SDL_RenderCopy(renderer, texture.texture, &texture.idle.frame_rects[texture.current_frame], &rect);
}
