#include "levelmap.h"

LevelMap::LevelMap() {
    w_ = h_ = x_ = y_ = -1;
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

LevelMap::LevelMap(const char* fname,SDL_Renderer* r) {
    rend = r;
    load_from_file(fname);
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
    wall.loadFromFile("assets/wall.png");
    wall.setRenderer(rend);
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
    fprintf(stderr,"Rendering floor %d\n",idx);
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

void LevelMap::render() {
    fprintf(stderr,"LM::r\n");
    for(int dx = x_ - VISION_RADIUS_MAX; dx < x_ + VISION_RADIUS_MAX; dx++) {
        if(dx >= 0 && dx < w_) {

            for(int dy = y_ - VISION_RADIUS_MAX; dy < y_ + VISION_RADIUS_MAX; dy++) {
                if(dy >= 0 && dy < h_) {
                    int screen_x = TILE_SIZE*(dx - x_ + VISION_RADIUS_MAX);
                    int screen_y = TILE_SIZE*(dy - y_ + VISION_RADIUS_MAX);
                    fprintf(stderr,"Rendering tile [%d][%d] at (%d,%d)\n",dx,dy,screen_x,screen_y);
                    fprintf(stderr,"w_ = %d, h_ = %d\n",w_,h_);
                    fprintf(stderr,"x_ = %d, y_ = %d\n",x_,y_);
                    switch(tiles[dx][dy]) {
                        case FLOOR:
                            fprintf(stderr,"floor\n");
                            random_floor()->render(screen_x,screen_y);
                            break;
                        case WALL:
                            fprintf(stderr,"wall\n");
                            wall.render(screen_x,screen_y);
                            wall.debug();
                            break;
                        default:
                            fprintf(stderr,"No tile at (%d,%d)\n",dx,dy);
                    }
                }
            }

        }
    } 
}
