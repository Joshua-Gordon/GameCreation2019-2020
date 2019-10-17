#pragma once
#include "../entity.h"

class DoNothing : public Entity {

public:
    DoNothing();
    DoNothing(int x,int y,AnimatedSprite& as, SDL_Renderer* r) : Entity(x,y,as,r){
        fprintf(stderr,"Correct donothing constructor has been called\n");
    }

    void update() override {
    }

};
