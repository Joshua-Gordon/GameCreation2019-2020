#include "player.h"

Player::Player() {
    rend = NULL;
}

Player::Player(const SDL_Renderer* r, LevelMap & l) {
    init(r,l);
}

void Player::init(const SDL_Renderer* r,LevelMap & l) {
    rend = r;
    fprintf(stderr,"About to cast renderer for player\n");
    SDL_Renderer* t_rend = const_cast<SDL_Renderer*>(rend); //Textures do not use const pointer
    fprintf(stderr,"Constructing player\n");
    as_walk_t[0].setRenderer(t_rend);
    as_walk_t[0].loadFromFile("assets/test_kirb.png");
    fprintf(stderr,"Creating animated sprite...\n");
    as_walk[0] = AnimatedSprite(&as_walk_t[0],0,0,2,1); //2 horiz frames 
    fprintf(stderr,"Created animated sprite!\n");

    lm = l;
}


void Player::handle(SDL_Event* e) {
    lm.handle(e);
}

void Player::update() {
    lm.update();
}

void Player::render(const GlobalState & gs) {
    fprintf(stderr,"Player render begin!\n");
    lm.render();
    fprintf(stderr,"Level render finish!\n");
    as_walk[0].render(RenderProxy(lm.getScreenW()/2,lm.getScreenH()/2),gs);
    fprintf(stderr,"Player render finish!\n");
}
