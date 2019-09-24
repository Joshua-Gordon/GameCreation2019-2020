#include "Texture.h"

#include <sys/stat.h>
#include <stdio.h>


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
    if(loadedSurface == NULL) {
        fprintf(stderr,"Could not load image %s!\n",path.c_str());
        fprintf(stderr,"Path is %s\n",path.c_str());
    } else {
        fprintf(stderr,"Loaded image %s!\n",path.c_str());
    }
    
    SDL_SetColorKey(loadedSurface,SDL_TRUE, SDL_MapRGB(loadedSurface->format,0xFF,0x00,0xFF));

    fprintf(stderr,"Renderer is: %p\n",renderer_);
    newTexture = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
    if(newTexture == NULL) {
        fprintf(stderr,"Could not create texture %s!\n",path.c_str());
    } else {
        fprintf(stderr,"Created texture %s!\n",path.c_str());
    }

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
    if(renderer_ == NULL) {
        fprintf(stderr,"renderer_ is NULL in Texture::render\n");
    }
    SDL_Rect renderQuad = {x,y,w_,h_};

    if(clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

	//fprintf(stderr, "T::r %p %d,%d,%d,%d @ (%d,%d)\n", clip, renderQuad.x, renderQuad.y, renderQuad.w, renderQuad.h,x,y);
	//if(clip) {
	//	fprintf(stderr, "T::r  - clip %d,%d,%d,%d\n", clip->x, clip->y, clip->w, clip->h);
	//}
    SDL_RenderCopy(renderer_, texture_,clip,&renderQuad);
}

int Texture::getWidth() const {
    return w_;
}

int Texture::getHeight() const {
    return h_;
}

void Texture::debug() {
    //fprintf(stderr,"Texture pointer %p\n",texture_);
}
