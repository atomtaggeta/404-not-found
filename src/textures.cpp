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
	// Player idle texture
	player.idle.texture = load_texture(renderer, PLAYER_IDLE_PATH);
	if (!player.idle.texture) { return false; }

	player.idle.frame_rects = new SDL_Rect[PLAYER_IDLE_FRAMES];

    for (int i = 0; i < PLAYER_IDLE_FRAMES; i++) {
        player.idle.frame_rects[i].x = i * PLAYER_WIDTH;
        player.idle.frame_rects[i].y = 0;
        player.idle.frame_rects[i].w = PLAYER_WIDTH;
        player.idle.frame_rects[i].h = PLAYER_HEIGHT;
    }

    player.idle.num_of_frames = PLAYER_IDLE_FRAMES;
    player.idle.current_frame = 1;
    player.idle.frame_start = SDL_GetTicks();
    player.idle.render_speed = PLAYER_IDLE_SPEED;

    // Player run texture
	player.run.texture = load_texture(renderer, PLAYER_RUN_PATH);
	if (!player.run.texture) { return false; }

	player.run.frame_rects = new SDL_Rect[PLAYER_RUN_FRAMES];

    for (int i = 0; i < PLAYER_RUN_FRAMES; i++) {
        player.run.frame_rects[i].x = i * PLAYER_WIDTH;
        player.run.frame_rects[i].y = 0;
        player.run.frame_rects[i].w = PLAYER_WIDTH;
        player.run.frame_rects[i].h = PLAYER_HEIGHT;
    }

    player.run.num_of_frames = PLAYER_RUN_FRAMES;
    player.run.current_frame = 1;
    player.run.frame_start = SDL_GetTicks();
    player.run.render_speed = PLAYER_RUN_SPEED;

    // Player jump up and down texture
	player.jump_up.texture = load_texture(renderer, PLAYER_JUMP_UP_PATH);
	if (!player.jump_up.texture) { return false; }

	player.jump_up.frame_rects = new SDL_Rect[PLAYER_JUMP_FRAMES];

    for (int i = 0; i < PLAYER_JUMP_FRAMES; i++) {
        player.jump_up.frame_rects[i].x = i * PLAYER_WIDTH;
        player.jump_up.frame_rects[i].y = 0;
        player.jump_up.frame_rects[i].w = PLAYER_WIDTH;
        player.jump_up.frame_rects[i].h = PLAYER_HEIGHT;
    }

    player.jump_down.texture = load_texture(renderer, PLAYER_JUMP_DOWN_PATH);
	if (!player.jump_down.texture) { return false; }

	player.jump_down.frame_rects = new SDL_Rect[PLAYER_JUMP_FRAMES];

    for (int i = 0; i < PLAYER_JUMP_FRAMES; i++) {
        player.jump_down.frame_rects[i].x = i * PLAYER_WIDTH;
        player.jump_down.frame_rects[i].y = 0;
        player.jump_down.frame_rects[i].w = PLAYER_WIDTH;
        player.jump_down.frame_rects[i].h = PLAYER_HEIGHT;
    }

    player.jump_up.num_of_frames = PLAYER_JUMP_FRAMES;
    player.jump_up.current_frame = 1;
    player.jump_up.frame_start = SDL_GetTicks();
    player.jump_up.render_speed = PLAYER_JUMP_SPEED;

    player.jump_down.num_of_frames = PLAYER_JUMP_FRAMES;
    player.jump_down.current_frame = 1;
    player.jump_down.frame_start = SDL_GetTicks();
    player.jump_down.render_speed = PLAYER_JUMP_SPEED;


    // Player attack texture
	player.attack.texture = load_texture(renderer, PLAYER_ATTACK_PATH);
	if (!player.attack.texture) { return false; }

	player.attack.frame_rects = new SDL_Rect[PLAYER_ATTACK_FRAMES];

    for (int i = 0; i < PLAYER_ATTACK_FRAMES; i++) {
        player.attack.frame_rects[i].x = i * PLAYER_WIDTH;
        player.attack.frame_rects[i].y = 0;
        player.attack.frame_rects[i].w = PLAYER_WIDTH;
        player.attack.frame_rects[i].h = PLAYER_HEIGHT;
    }

    player.attack.num_of_frames = PLAYER_ATTACK_FRAMES;
    player.attack.current_frame = 1;
    player.attack.frame_start = SDL_GetTicks();
    player.attack.render_speed = PLAYER_ATTACK_SPEED;

	return true;
}

// Deload all the textures
bool Textures::deload() {
	// Player texture
	SDL_DestroyTexture(player.idle.texture);
	delete player.idle.frame_rects;

	return true;
}
