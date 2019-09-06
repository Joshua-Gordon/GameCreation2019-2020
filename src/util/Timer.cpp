#include "Timer.h"

Timer::Timer() {
    startTicks_ = 0;
    pauseTicks_ = 0;

    started_ = false;
    paused_ = false;
}

void Timer::start() {
    started_ = true;
    paused_ = false;

    startTicks_ = SDL_GetTicks();
    pauseTicks_ = 0;
}

void Timer::stop() {
    started_ = false;
    paused_ = false;

    startTicks_ = 0;
    pauseTicks_ = 0;
}

void Timer::pause() {
    if(started_ && !paused_) {
        paused_ = true;

        pauseTicks_ = SDL_GetTicks() - startTicks_;
        startTicks_ = 0;
    }
}

void Timer::unpause() {
    if(started_ && paused_) {
        paused_ = false;
        
        startTicks_ = SDL_GetTicks() - pauseTicks_;
        pauseTicks_ = 0;
    }
}

Uint32 Timer::getTicks() {
    Uint32 time = 0;

    if(started_) {
        if(paused_) {
            time = pauseTicks_;
        } else {
            time = SDL_GetTicks() - startTicks_;
        }
    }

    return time;
}

bool Timer::isStarted() {
    return started_;
}

bool Timer::isPaused() {
    return paused_;
}
