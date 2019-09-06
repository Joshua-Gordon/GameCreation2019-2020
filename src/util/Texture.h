#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern SDL_Renderer* renderer;

class Texture {
private:
    SDL_Texture* texture_;

    int w_,h_;

public:
    Texture();
    Texture(SDL_Texture* t,int w, int h) : texture_(t), w_(w), h_(h) {}
    ~Texture();

    bool loadFromFile(std::string path);

    void free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    
    void render(int x, int y, SDL_Rect* clip = NULL);

    int getWidth();
    int getHeight();
};
