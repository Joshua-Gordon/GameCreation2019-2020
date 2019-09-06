#include "Texture.h"

#include <sys/stat.h>


Texture::Texture() {
    texture_ = NULL;
    w_ = -1;
    h_ = -1;
}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(std::string path) {

    struct stat buf;

#ifdef EXISTS_CHECK
    if(stat(path.c_str(),&buf) != 0) {
        return false;
    }
#endif
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    
    SDL_SetColorKey(loadedSurface,SDL_TRUE, SDL_MapRGB(loadedSurface->format,0xFF,0x00,0xFF));

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    w_ = loadedSurface->w;
    h_ = loadedSurface->h;

    texture_ = newTexture;

    return true;
}

void Texture::free() {
    if(texture_ != NULL) {
        SDL_DestroyTexture(texture_);
        w_ = -1;
        h_ = -1;
    }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(texture_,red,green,blue);
}

void Texture::render(int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = {x,y,w_,h_};

    if(clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(renderer, texture_,clip,&renderQuad);
}

int Texture::getWidth() {
    return w_;
}

int Texture::getHeight() {
    return h_;
}
