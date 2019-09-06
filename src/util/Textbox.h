#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
using std::string;

#include "Texture.h"

#define SANS "Sans.ttf"

//To add: color
Texture getTextBox(SDL_Renderer* renderer, const string & font, int size, const string & text);
