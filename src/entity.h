#pragma once
#include "animatedsprite.h"

#define TILE_SIZE 64

class Entity {
    private:
        int x_,y_; //coordinates in level
        bool active;
        AnimatedSprite as_;

        SDL_Renderer* rend;

    public:
        Entity();
        Entity(int x, int y, AnimatedSprite& as, SDL_Renderer* r) : x_(x),y_(y),as_(as),rend(r){active=false;fprintf(stderr,"Correct entity constructor\n");}

        int getx(){return x_;}
        int gety(){return y_;}
        bool isactive(){return active;}
        
        virtual void update();
        virtual void render(const GlobalState&, int,int,int,int); //GlobalState, and player xy, and screen dimensions

};
