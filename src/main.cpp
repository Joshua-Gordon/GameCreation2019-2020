#include "game.h"
#include <cstdlib>


int main(int argc, char** argv) {
	Game game;
    if(argc == 3) {
        game.debug(atoi(argv[1]),atoi(argv[2]));
    }
	game.run();
    return 0;
}
