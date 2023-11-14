#include "Timer.hpp"
#include <iostream>
//#include <Windows.h>
//#include <thread>
//#include <chrono>

Timer* Timer::Timer_Instance = nullptr;

void Timer::getTick()
{
	Timer_DeltaTime = (SDL_GetTicks64() - Timer_LastTime);

	if ((Timer_DeltaTime < TARGET_DELTATIME) and fpslock) {
		SDL_Delay(TARGET_DELTATIME - Timer_DeltaTime);
		Timer_DeltaTime = TARGET_DELTATIME;
		countedframes++;
	}
	/*else if (fps > 400) {
		SDL_Delay(1000 / 400 - Timer_DeltaTime);
		Timer_DeltaTime = 1000 / 400;
		std::cout << Timer_DeltaTime;
		countedframes++;
	}*/
	else { countedframes++; }

	sec += Timer_DeltaTime;
	fps = countedframes / (sec / 1000.0);
	sec = sec > 1000 ? 0 : sec;
	countedframes = sec == 0 ? 0 : countedframes;

	pressedtimer = !pressed ? 0 : pressedtimer-=Timer_DeltaTime;
	pressed = pressedtimer <= 0?false : true;

	//std::cout << TARGET_DeltaTime - Timer_DeltaTime << "\n";

	//fps = 1000.0 / (SDL_GetTicks64() - Timer_LastTime); // f/s = d | s*d = f | f*d = s = 1 (f helyesebb ugy hogy frame time)

	Timer_LastTime = SDL_GetTicks64();
	//std::cout << fps << " " << Timer_DeltaTime << "\n";
}

bool Timer::pressable(Uint64 time)
{
	pressedtimer = pressedtimer == 0 ? time : pressedtimer;
	//pressedtimer = time;

	if (pressedtimer == time) {
		pressed = true;
		return true;
	}
	else {

		return false;
	}
}
