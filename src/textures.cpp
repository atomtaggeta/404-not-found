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
	player = load_texture(renderer, PLAYER_PATH);
	if (!player) { return false; }

	return true;
}

// Deload all the textures
bool Textures::deload() {
	SDL_DestroyTexture(player);
	return true;
}
