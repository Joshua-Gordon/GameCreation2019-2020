#include "player.h"

Player::Player() {
    rend = NULL;
}

Player::Player(const SDL_Renderer* r, LevelMap & l) {
    init(r,l);
}

void Player::init(const SDL_Renderer* r,LevelMap & l) {
    rend = r;
    SDL_Renderer* t_rend = const_cast<SDL_Renderer*>(rend); //Textures do not use const pointer
    as_walk_t[0].setRenderer(t_rend);
    as_walk_t[0].loadFromFile("assets/ACB.png");
    as_walk_t[1].setRenderer(t_rend);
    as_walk_t[1].loadFromFile("assets/ACF.png");
    as_walk_t[2].setRenderer(t_rend);
    as_walk_t[2].loadFromFile("assets/ACL.png");
    as_walk_t[3].setRenderer(t_rend);
    as_walk_t[3].loadFromFile("assets/ACR.png");
    as_walk[0] = AnimatedSprite(&as_walk_t[0],0,0,2,1); //2 horiz frames 
    as_walk[1] = AnimatedSprite(&as_walk_t[1],0,0,2,1); //2 horiz frames 
    as_walk[2] = AnimatedSprite(&as_walk_t[2],0,0,2,1); //2 horiz frames 
    as_walk[3] = AnimatedSprite(&as_walk_t[3],0,0,2,1); //2 horiz frames 

    lm = l;
    dir = 0;
}


void Player::handle(SDL_Event* e) {
    if(e->type == SDL_KEYDOWN && e->key.repeat == 0) {
        switch(e->key.keysym.sym) {
            case SDLK_UP:
                dir = 0;
                break;
            case SDLK_DOWN:
                dir = 1;
                break;
            case SDLK_LEFT:
                dir = 2;
                break;
            case SDLK_RIGHT:
                dir = 3;
                break;
        }
    }
    lm.handle(e);
}

void Player::update() {
    lm.update();
}

void Player::render(const GlobalState & gs) {
    fprintf(stderr,"Player render begin!\n");
    lm.render();
    fprintf(stderr,"Level render finish!\n");
    as_walk[dir].render(RenderProxy(lm.getScreenW()/2,lm.getScreenH()/2),gs);
    fprintf(stderr,"Player render finish!\n");
}
