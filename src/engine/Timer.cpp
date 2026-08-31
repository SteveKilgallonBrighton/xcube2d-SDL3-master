#include "Timer.h"

Timer::Timer() : time(0) {}

void Timer::measure() {
	time = SDL_GetTicks();
}

void Timer::reset() {
	time = 0;
}

Uint64 Timer::getTime() {
	return time;
}

Uint64 Timer::getElapsed() {
	if (time == 0) return 0; // ensure time is not zero to avoid negative elapsed time
	return SDL_GetTicks() - time;
	//return SDL_GetTicks() - time;
}