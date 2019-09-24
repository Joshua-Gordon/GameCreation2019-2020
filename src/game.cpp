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

	SDL_SetRenderDrawColor(renderer_, 0x77, 0x00, 0x77, 0xff);

	text_t = getTextBox(renderer_, "assets/Sans.ttf", 24, "yolo swaggins");
	text_ = Sprite(&text_t, 100, 200);
	pizza_t.setRenderer(renderer_);
	pizza_t.loadFromFile("pizza.png");
	pizza_ = Sprite(&pizza_t, 0, 100);
	ply_t.setRenderer(renderer_);
	ply_t.loadFromFile("assets/char_walk_forward.png");
	ply_ = AnimatedSprite(&ply_t, 0, 100, 3, 1);
	pizza_.addChild(&ply_);
	text_.addChild(&pizza_);
	root_.addChild(&text_);
    fprintf(stderr,"Loading map...\n");
    lm.setRenderer(renderer_);
    lm.load_from_file("assets/test_map2.png");
    lm.setScreenSize(S_W,S_H);
    lm.setLocation(1,1);
    fprintf(stderr,"Loaded map!\n");

    p.init(renderer(),lm);
    fprintf(stderr,"Player init finished\n");

}

Game::~Game() {
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
        update();
		SDL_RenderPresent(renderer_);

		frames_++;
		int ticks = fps.getTicks();
		if(ticks < TICK_RATE) {
			SDL_Delay(TICK_RATE - ticks);
		}
	}
}

void Game::handle(SDL_Event &e) {
	if(e.type == SDL_QUIT) {
		stop();
	}
    p.handle(&e);
	if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q) {
		stop();
	}
}

void Game::render() {
    fprintf(stderr,"Render\n");
    p.render(globalState());
	//text_.setX(100 + frames_);
	//root_.render(RenderProxy(), globalState());
}

void Game::update() {
    p.update();
}
