#include <SDL2/SDL.h>

#define STATE_L1 0
//Level 1; the factory
#define STATE_L2 1
//Level 2; the outside
#define STATE_L3 2
//Level 3; the tower
#define STATE_PAUSE 3
//Pause menu; options & quit
#define STATE_INVENTORY 4
//Inventory; manage and equip parts

class Game {
    private:
        int state;
        SDL_Renderer* rend;

    public:
        
        Game(SDL_Renderer* r) : rend(r){}
        ~Game();
};
