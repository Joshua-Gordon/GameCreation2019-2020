#include <stdio.h>
#include <string>
using std::string;
using std::to_string;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "util/Texture.h"

#define NUM_FLOORS 8
#define TILE_SIZE 64

#define FLOOR 16777215 //white
#define WALL 0 //black

//#define VISION_RADIUS_MAX 5

#define SPEED 1

class LevelMap {
    private:

        int S_W,S_H;

        int w_,h_;
        int x_,y_; //player's location a.k.a. where the camera is
        int vx_,vy_;
        int zoom_level;
        int** tiles;
        Texture floor_textures[NUM_FLOORS];
        Texture wall;

        Texture* random_floor();

        SDL_Renderer* rend;

    public:
        LevelMap();
        LevelMap(const char*,SDL_Renderer*,int,int);
        ~LevelMap();

        void setLocation(int x, int y) {x_ = x; y_ = y;}

        void setRenderer(SDL_Renderer* r){rend = r;}
        void setScreenSize(int w, int h) {S_W = w; S_H = h;}
        void load_from_file(const char*);
        void print();

        void render();
        void handle(SDL_Event*);
        void update();

};
