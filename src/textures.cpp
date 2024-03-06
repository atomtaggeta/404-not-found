#include "textures.h"

Textures::Textures(SDL_Renderer* renderer) : renderer(renderer) {
}

Textures::~Textures() {
}

// Loads and returns a texture using the renderer from the given file path
SDL_Texture* Textures::load_texture(SDL_Renderer* renderer, const char* file_path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, file_path);
    if (!texture) {
        printf("Unable to load texture from %s! SDL Error: %s\n", file_path, SDL_GetError());
        return nullptr;
    }

    return texture;
}

// Load all the textures
bool Textures::load() {
	// Player texture
	player.texture = load_texture(renderer, PLAYER_IDLE_PATH);
	if (!player.texture) { return false; }

	player.frame_rects = new SDL_Rect[PLAYER_FRAMES];

    for (int i = 0; i < PLAYER_FRAMES; i++) {
        player.frame_rects[i].x = i * PLAYER_WIDTH;
        player.frame_rects[i].y = 0;
        player.frame_rects[i].w = PLAYER_WIDTH;
        player.frame_rects[i].h = PLAYER_HEIGHT;
    }

    player.num_of_frames = PLAYER_FRAMES;
    player.current_frame = 1;
    player.frame_start = SDL_GetTicks();
    player.render_speed = PLAYER_RENDER_SPEED;

	return true;
}

// Deload all the textures
bool Textures::deload() {
	// Player texture
	SDL_DestroyTexture(player.texture);
	delete player.frame_rects;

	return true;
}
