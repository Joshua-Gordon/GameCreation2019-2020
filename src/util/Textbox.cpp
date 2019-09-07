#include "Textbox.h"

#include <stdio.h>

Texture getTextBox(SDL_Renderer* renderer, const string & font, int size, const string & text) {
    
	fprintf(stderr, "gTB: renderer %p\n", renderer);
    TTF_Font* font_ = TTF_OpenFont(font.c_str(),size);
    if(font_ == NULL) {
        printf("Could not load font!\n");
    }
    SDL_Color color = {0x00,0xff,0x00}; //green

    SDL_Surface* m_surface = TTF_RenderText_Solid(font_,text.c_str(),color);

    SDL_Texture* m_texture = SDL_CreateTextureFromSurface(renderer,m_surface);

    int w = -1, h = -1;
    TTF_SizeText(font_,text.c_str(),&w,&h);

    return Texture(renderer, m_texture,w,h);

}
