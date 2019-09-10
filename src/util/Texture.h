#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Texture {
private:
	SDL_Renderer *renderer_;
    SDL_Texture* texture_;

    int w_,h_;

public:
    Texture() : renderer_(NULL), texture_(NULL), w_(-1), h_(-1) {}
	Texture(SDL_Renderer *r) : renderer_(r), texture_(NULL), w_(-1), h_(-1) {}
    Texture(SDL_Renderer *r, SDL_Texture* t,int w, int h) : renderer_(r), texture_(t), w_(w), h_(h) {}

	void setRenderer(SDL_Renderer *r) { renderer_ = r; }

    bool loadFromFile(std::string path);

    void free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    
    void render(int x, int y, SDL_Rect* clip = NULL);

    int getWidth() const;
    int getHeight() const;

    void debug();
};
