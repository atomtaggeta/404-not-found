#include "game.h"

// https://github.com/aminosbh/sdl2-samples-and-projects

int main() {
    Game game;
    if (!game.init()) {
        printf("Failed to initialize the game!\n");
        return 1;
    }

    game.run();

    // TODO: MOVE SIMPLE GAME LOGIC HERE

    return 0;
}
