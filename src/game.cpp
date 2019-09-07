#include <stdio.h>

#include "game.h"

#define ABORT(...) do { \
	fprintf(stderr, __VA_ARGS__); \
	exit(1); \
} while(0)

#define CHECK(call) do { \
    if(call < 0) { \
        ABORT("Error on %s, SDL_Error is: %s\n",#call,SDL_GetError()); \
        exit(1); \
    } \
} while(0)

Game::Game() : timer_(), frames_(0), running_(false) {
    CHECK(SDL_Init(SDL_INIT_VIDEO)); //Video
    CHECK(IMG_Init(IMG_INIT_PNG));   //PNG
    CHECK(TTF_Init());

	if(!(window_ = SDL_CreateWindow(
			TITLE,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			S_W,
			S_H,
			SDL_WINDOW_SHOWN
	))) {
		ABORT("Window creation failed: %s\n", SDL_GetError());
	}

	if(!(renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED))) {
		ABORT("Renderer creation failed: %s\n", SDL_GetError());
	}

	SDL_SetRenderDrawColor(renderer_, 0xff, 0x00, 0xff, 0xff);

	fprintf(stderr, "G::G: renderer %p\n", renderer_);

	scene_ = getTextBox(renderer_, "assets/Sans.ttf", 24, "plz work yo");
	image_.setRenderer(renderer_);
	image_.loadFromFile("pizza.png");
}

Game::~Game() {
	scene_.free();
	image_.free();
	SDL_DestroyRenderer(renderer_);
	renderer_ = NULL;
	SDL_DestroyWindow(window_);
	window_ = NULL;

	IMG_Quit();
	SDL_Quit();
	fprintf(stderr, "Thank you for playing Wing Commander\n");
}

void Game::run() {
	SDL_Event e;
	Timer fps;

	timer_.start();
	running_ = true;

	while(running_) {
		fps.start();

		while(SDL_PollEvent(&e)) {
			handle(e);
		}

		SDL_RenderClear(renderer_);
		render();
		SDL_RenderPresent(renderer_);

		frames_++;
		int ticks = fps.getTicks();
		if(ticks < TICKS_PER_FRAME) {
			SDL_Delay(TICKS_PER_FRAME - ticks);
		}
	}
}

void Game::handle(SDL_Event &e) {
	if(e.type == SDL_QUIT) {
		stop();
	}

	if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q) {
		stop();
	}
}

void Game::render() {
	fprintf(stderr, "%u %d %d\n", frames_, scene_.getWidth(), scene_.getHeight());
	fprintf(stderr, "G::r: renderer %p\n", renderer_);
	scene_.render(100 + frames_, 200);
	image_.render(100 + frames_, 300);
}
