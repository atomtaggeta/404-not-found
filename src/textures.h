#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Frames {
    SDL_Texture* texture;
    SDL_Rect* frame_rects;
};

struct Texture {
    struct Frames idle;
    struct Frames run;

    int num_of_frames;
    int current_frame;
    Uint32 frame_start;
    float render_speed;
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

    const float PLAYER_RENDER_SPEED = 1.5;

    const int PLAYER_WIDTH = 120;
    const int PLAYER_HEIGHT = 80;
    const int PLAYER_FRAMES = 10;
};

#endif // TEXTURES_H
