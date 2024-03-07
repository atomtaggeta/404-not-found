#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Frames {
    SDL_Texture* texture;
    SDL_Rect* frame_rects;

    int current_frame;
    int num_of_frames;
    Uint32 frame_start;
    float render_speed;
};

struct Texture {
    struct Frames idle;
    struct Frames run;
    struct Frames jump_up;
    struct Frames jump_down;
    struct Frames attack;
};

class Textures {
public:
    Textures(SDL_Renderer* renderer);
    ~Textures();

    bool load();
    bool deload();

    struct Texture player;

private:
    SDL_Renderer* renderer;

    SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file_path);

    const char* PLAYER_IDLE_PATH = "assets/characters/player/idle.png";
    const char* PLAYER_RUN_PATH = "assets/characters/player/run.png";
    const char* PLAYER_JUMP_UP_PATH = "assets/characters/player/jump_up.png";
    const char* PLAYER_JUMP_DOWN_PATH = "assets/characters/player/jump_down.png";
    const char* PLAYER_ATTACK_PATH = "assets/characters/player/attack.png";

    const int PLAYER_IDLE_FRAMES = 10;
    const int PLAYER_RUN_FRAMES = 10;
    const int PLAYER_JUMP_FRAMES = 3;
    const int PLAYER_ATTACK_FRAMES = 4;

    const float PLAYER_IDLE_SPEED = 1.5;
    const float PLAYER_RUN_SPEED = 1.5;
    const float PLAYER_JUMP_SPEED = 1.5;
    const float PLAYER_ATTACK_SPEED = 1.0;

    const int PLAYER_WIDTH = 120;
    const int PLAYER_HEIGHT = 80;
};

#endif // TEXTURES_H
