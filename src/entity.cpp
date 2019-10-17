#include "entity.h"

Entity::Entity() {
    x_ = y_ = -1;
    rend = NULL;
    fprintf(stderr,"Empty entity constructor called!\n");
}

void Entity::update() {
    fprintf(stderr,"ERROR: RAW ENTITY UPDATING\n");
}

void Entity::render(const GlobalState& gs, int px, int py,int S_W,int S_H) {
    fprintf(stderr,"Entity render vardump:\n---------\ntexture=%p,px=%d,py=%d\nx_=%d,y_=%d\n---------\n",as_.texture(),px,py,x_,y_);
    if(px*TILE_SIZE - x_*TILE_SIZE < S_W && py*TILE_SIZE - y_*TILE_SIZE < S_H) {
        int sx = TILE_SIZE*(x_ - px) + S_W/2;
        int sy = TILE_SIZE*(y_ - py) + S_H/2;
        as_.render(RenderProxy(sx,sy),gs);
        fprintf(stderr,"Entity rendering at %d,%d\n",sx,sy);
    } else {
        fprintf(stderr,"Entity is off screen at x_=%d,y_=%d\n",x_,y_);
    }
}
