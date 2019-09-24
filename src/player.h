#pragma once
#include <SDL2/SDL.h>

#include "levelmap.h"
#include "animatedsprite.h"
#include "renderproxy.h"

class Player {

private:
    int dir;    
    Texture as_walk_t[4];
    AnimatedSprite as_walk[4]; //DOWN,UP,LEFT,RIGHT 
    AnimatedSprite swing;
    //put sound effects here
    LevelMap lm;
    bool has_manip; //can open doors

    const SDL_Renderer* rend;

public:

    Player();
    Player(const SDL_Renderer*,LevelMap&);

    void init(const SDL_Renderer*,LevelMap&);

    void setRenderer(const SDL_Renderer* r){rend = r;}
    void setMap(LevelMap l){lm = l;}

    void handle(SDL_Event*);
    void update();
    void render(const GlobalState &);

    void see(); //Enumerates nearby tiles and sets visibility 
                //Render unsets visibilitiy


};
