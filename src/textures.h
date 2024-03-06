#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Texture {
    SDL_Texture* texture;
    SDL_Rect* frame_rects;

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
    const int PLAYER_WIDTH = 120;
    const int PLAYER_HEIGHT = 80;
    const int PLAYER_FRAMES = 10;
    const float PLAYER_RENDER_SPEED = 1.0;
};

#endif // TEXTURES_H
