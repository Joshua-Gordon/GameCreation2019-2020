#include <SDL2/SDL.h>

#include "levelmap.h"
#include "animatedsprite.h"
#include "renderproxy.h"

class Player {

private:
    int dir;    
    AnimatedSprite as_walk[4]; //DOWN,UP,LEFT,RIGHT 
    AnimatedSprite swing;
    //put sound effects here
    LevelMap lm;

public:

    Player();
    ~Player();

    void handle(SDL_Event*);
    void update();
    void render(const GlobalState &);
     


};
