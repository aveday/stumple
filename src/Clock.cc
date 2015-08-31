#include <SDL2/SDL.h>

#include "Clock.h"

Clock::Clock(): time(0) { }

int Clock::GetTimeDiff() {
    // TODO handle int overflow (possible in long sessions)
    int newTime = SDL_GetTicks();
    int diff = newTime - time;
    time = newTime;
    return diff;
}

int Clock::GetTime() {
    return time;
}

int Clock::Sleep() {
    int delay = MSPF - GetTimeDiff();
    if(delay < 0)
        return 1;
    SDL_Delay(delay);
    return delay;
}
