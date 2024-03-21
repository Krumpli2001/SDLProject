#include "Timer.hpp"
#include <iostream>


Timer* Timer::Timer_Instance = nullptr;

void Timer::getTick()
{
	Timer_DeltaTime = (SDL_GetTicks64() - Timer_LastTime);


	if (((Timer_DeltaTime < TARGET_DELTATIME) and fpslock) or (Timer_DeltaTime < TARGET_DELTATIME and menu)) {
		SDL_Delay(static_cast<Uint32>(TARGET_DELTATIME - Timer_DeltaTime));
		Timer_DeltaTime = static_cast<Uint64>(TARGET_DELTATIME);
		countedframes++;
	}
	else if (Timer_DeltaTime < (1000 / 500)) {
		SDL_Delay(static_cast<Uint32>((1000 / 500) - Timer_DeltaTime));
		Timer_DeltaTime = 1000 / 500;
		countedframes++;
	}
	else { countedframes++; }

	sec += Timer_DeltaTime;
	fps = static_cast<int>(countedframes / (sec / 1000.0));
	sec = sec > 1000 ? 0 : sec;
	countedframes = sec == 0 ? 0 : countedframes;

	pressedtimer = !pressed ? 0 : pressedtimer -= static_cast<int>(Timer_DeltaTime);
	pressed = pressedtimer <= 0?false : true;

	Timer_LastTime = SDL_GetTicks64();
}

bool Timer::pressable(Uint32 time)
{
	pressedtimer = pressedtimer == 0 ? static_cast<int>(time) : pressedtimer;

	if (pressedtimer == time) {
		pressed = true;
		return true;
	}
	else {
		return false;
	}
}
