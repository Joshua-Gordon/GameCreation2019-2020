#pragma once

#include <SDL2/SDL.h>

#include "util/Timer.h"
#include "util/Texture.h"
#include "util/Textbox.h"

#define TITLE "cool preprocessor title"
#define S_W 1280
#define S_H 960
#define MAX_FPS 60
#define TICKS_PER_FRAME (1000 / MAX_FPS)

class Game {
	protected:
		SDL_Renderer *renderer_;
		SDL_Window *window_;

		Timer timer_;
		unsigned frames_;
		bool running_;

		Texture scene_;
		Texture image_;

	public:
		Game();
		~Game();

		SDL_Renderer *renderer() { return renderer_; }
		SDL_Window *window() { return window_; }
		Timer *timer() { return &timer_; }
		unsigned frames() { return frames_; }
		bool running() { return running_; }
		void stop() { running_ = false; }

		void run();
		void handle(SDL_Event &);
		void render();
};