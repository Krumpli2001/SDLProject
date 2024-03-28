#include "Timer.hpp"
#include <iostream>


Timer* Timer::Timer_Instance = nullptr;

void Timer::getTick()
{
	Timer_DeltaTime = (SDL_GetTicks64() - Timer_LastTime);

	constexpr auto egy_masodperc = 1000.0;
	constexpr auto maxFPS = 500;
	if (((Timer_DeltaTime < TARGET_DELTATIME) and fpslock) or (Timer_DeltaTime < TARGET_DELTATIME and menu)) {
		SDL_Delay(static_cast<Uint32>(TARGET_DELTATIME - Timer_DeltaTime));
		Timer_DeltaTime = static_cast<Uint64>(TARGET_DELTATIME);
		countedframes++;
	}
	else if (Timer_DeltaTime < (egy_masodperc / maxFPS)) {
		SDL_Delay(static_cast<Uint32>((egy_masodperc / maxFPS) - Timer_DeltaTime));
		Timer_DeltaTime = egy_masodperc / maxFPS;
		countedframes++;
	}
	else { countedframes++; }

	sec += Timer_DeltaTime;
	fps = static_cast<int>(countedframes / (sec / egy_masodperc));
	sec = sec > egy_masodperc ? 0 : sec;
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
