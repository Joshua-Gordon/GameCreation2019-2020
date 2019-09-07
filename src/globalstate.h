#pragma once

#include <SDL2/SDL.h>
#include "util/Timer.h"

class GlobalState {
	public:
		SDL_Renderer *renderer;
		SDL_Window *window;
		const Timer *timer;
		unsigned frames;
		bool running;
};

