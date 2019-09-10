#pragma once

#include <SDL2/SDL.h>

#include "util/Timer.h"
#include "util/Texture.h"
#include "util/Textbox.h"
#include "sprite.h"
#include "scene.h"
#include "animatedsprite.h"
#include "globalstate.h"
#include "levelmap.h"

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

		Scene root_;
		Sprite text_, pizza_;
		AnimatedSprite ply_;
		Texture text_t, pizza_t, ply_t;

        LevelMap lm;

	public:
		Game();
		~Game();

		const SDL_Renderer *renderer() const { return renderer_; }
		const SDL_Window *window() const { return window_; }
		const Timer *timer() const { return &timer_; }
		unsigned frames() const { return frames_; }
		bool running() const { return running_; }
		const Scene *root() const { return &root_; }

		const GlobalState globalState() const {
			return GlobalState {
				renderer_,
				window_,
				&timer_,
				frames_,
				running_
			};
		}

		void stop() { running_ = false; }

		void run();
		void handle(SDL_Event &);
		void render();
};
