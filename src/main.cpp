#include <stdio.h>

#include <SDL2/SDL.h>
#include "util/Timer.h"
#include "util/Texture.h"
#include "util/Textbox.h"

/* CONSTANTS */
#define TITLE "cool preprocessor title"

#define S_W 1280
#define S_H 960

#define MAX_FPS 60
#define TICKS_PER_FRAME 16 //Integer division of 1000 / 60

#define TILE_SIZE 64

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void init();
void close();

Timer fps_timer;
Timer cap_timer;
int frames_since_start;

int main(int argc, char** argv) {

    init();

    printf("Init done\n");

    fps_timer.start();
    frames_since_start = 0;

    SDL_Event e;
    bool done = false;

    Texture text = getTextBox(renderer,"assets/Sans.ttf",24,"work plz");

    while(!done) { //game loop
        cap_timer.start();
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                done = true;
                break;
            }
            if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_q) {
                    done = true;
                    break;
                }
            }
        } //input is handled

        SDL_RenderClear(renderer);
    
        //render stuff
        text.render(100 + frames_since_start,200);
        
        SDL_RenderPresent(renderer);

        ++frames_since_start;
        int num_ticks = cap_timer.getTicks();
        if(num_ticks < TICKS_PER_FRAME) {
            SDL_Delay(TICKS_PER_FRAME-num_ticks);
        }
    }

    close();
    return 0;
}

#define CHECK(call) do { \
    if(call < 0) { \
        printf("Error on %s, SDL_Error is: %s\n",#call,SDL_GetError()); \
        exit(1); \
    } \
} while(0);

void init() {
    CHECK(SDL_Init(SDL_INIT_VIDEO)); //Video
    CHECK(IMG_Init(IMG_INIT_PNG));   //PNG
    CHECK(TTF_Init());

    window = SDL_CreateWindow(TITLE,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,S_W,S_H,SDL_WINDOW_SHOWN);
    if(window == NULL) {
        printf("Could not create window\n");
        exit(2);
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        printf("Could not create renderer\n");
        exit(3);
    }

    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
}

void close() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
    printf("Thank you for playing wing commander\n");
}
