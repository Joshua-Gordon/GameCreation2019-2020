#pragma once

#include <SDL2/SDL.h>

class Timer {

private:
    Uint32 startTicks_,pauseTicks_;

    bool paused_,started_;

public:
    
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 getTicks();

    bool isStarted();
    bool isPaused();
};
