#include "levelmap.h"

LevelMap::LevelMap() {
    w_ = h_ = x_ = y_ = 0;
    vx_ = vy_ = 0;
    zoom_level = -1;
    tiles = NULL;
}

//This function is copy-pasted from the internet
Uint32 getpixel(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

LevelMap::LevelMap(const char* fname,SDL_Renderer* r, int w, int h) {
    rend = r;
    load_from_file(fname);
    S_W = w;
    S_H = h;
}

void LevelMap::load_from_file(const char* fname) {
    SDL_Surface* loaded_surface = IMG_Load(fname);
    fprintf(stderr,"Surface is loaded\n");
    w_ = loaded_surface->w;
    h_ = loaded_surface->h;
    tiles = (int**)malloc(sizeof(int*)*w_);
    fprintf(stderr,"Tiles are alloc'd\n");
    zoom_level = 1;
    for(int x = 0; x < w_; ++x) {
        tiles[x] = (int*)malloc(sizeof(int)*h_);
        for(int y = 0; y < h_; ++y) {
            tiles[x][y] = getpixel(loaded_surface,x,y);
        }
    }
    fprintf(stderr,"Tiles are really alloc'd\n");
    for(int i = 0; i < NUM_FLOORS; ++i) {
        string path = "assets/rust_"+to_string(i)+".png";
        fprintf(stderr,"Path: %s\n",path.c_str());
        floor_textures[i] = Texture();
        floor_textures[i].setRenderer(rend);
        floor_textures[i].loadFromFile(path);
        floor_textures[i].debug();
    }
    wall.setRenderer(rend);
    wall.loadFromFile("assets/wall.png");
    fprintf(stderr,"Assets are loaded\n");
}

LevelMap::~LevelMap() {
    for(int x = 0; x < w_; ++x) {
        free(tiles[x]);
    }
    free(tiles);
}

Texture* LevelMap::random_floor() {
    int idx = rand() % NUM_FLOORS;
    //fprintf(stderr,"Rendering floor %d\n",idx);
    return floor_textures + idx;
}

void LevelMap::print() {
    for(int x = 0; x < w_; ++x) {
        for(int y = 0; y < h_; ++y) {
            printf("%d",tiles[x][y]);
        }
        printf("\n");
    }
}

void LevelMap::render() { //needs rewrite
   
    int viz_x = (S_W/2)/TILE_SIZE;
    int viz_y = (S_H/2)/TILE_SIZE;

    for(int dx = x_ - viz_x; dx < x_ + viz_x; ++dx) {

        if(dx >= 0 && dx < w_) {

            for(int dy = y_ - viz_y; dy < y_ + viz_y; ++dy) {

                if(dy >= 0 && dy < h_) {

                    int screen_x = S_W/2 + (dx - x_)*TILE_SIZE;
                    int screen_y = S_H/2 + (dy - y_)*TILE_SIZE;

                    if(0 < tiles[dx][dy] && tiles[dx][dy] <= 8) {
                        floor_textures[tiles[dx][dy]-1].render(screen_x,screen_y);
                    } else if(tiles[dx][dy] == WALL) {
                        wall.render(screen_x,screen_y);
                    } else if(tiles[dx][dy] == FLOOR) {
                        tiles[dx][dy] = 1+(rand() % NUM_FLOORS);
                        floor_textures[tiles[dx][dy]-1].render(screen_x,screen_y);
                    }

                }

            }

        }

    } 

}


void LevelMap::handle(SDL_Event* e) {
    if(e->type == SDL_KEYDOWN && e->key.repeat == 0) {
        switch(e->key.keysym.sym) { //NOTE TO SELF: THIS IS *BACKWARDS*
            case SDLK_UP:
                vy_ += SPEED;
                break;
            case SDLK_DOWN:
                vy_ -= SPEED;
                break;
            case SDLK_LEFT:
                vx_ += SPEED;
                break;
            case SDLK_RIGHT:
                vx_ -= SPEED;
                break;
        }
        //Velocity is set
    } else if(e->type == SDL_KEYUP && e->key.repeat == 0) {
        switch(e->key.keysym.sym) {
            case SDLK_UP:
            case SDLK_DOWN:
                vy_ = 0;
                break;
            case SDLK_LEFT:
            case SDLK_RIGHT:
                vx_ = 0;
                break;
        }
        //Velocity is unset
    }
}

void LevelMap::update() {
    //move and do collision checking
    fprintf(stderr,"Player is at: (%d,%d)\n",x_,y_);
    x_ += vx_;
    int tile = tiles[x_][y_];
    if(tile == WALL) {
        x_ -= vx_;
        fprintf(stderr,"Collision at x_ = %d\n",x_);
    }
    y_ += vy_;
    tile = tiles[x_][y_];
    if(tile == WALL) {
        y_ -= vy_;
        fprintf(stderr,"Collision at y_ = %d\n",y_);
    }

}
