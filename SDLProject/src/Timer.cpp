#include "Timer.hpp"
#include <iostream>
//#include <Windows.h>
//#include <thread>
//#include <chrono>

Timer* Timer::Timer_Instance = nullptr;

void Timer::getTick()
{
	Timer_DeltaTime = (SDL_GetTicks64() - Timer_LastTime);

	if ((Timer_DeltaTime < TARGET_DeltaTime) and fpslock) {
		SDL_Delay(TARGET_DeltaTime - Timer_DeltaTime);
		Timer_DeltaTime = TARGET_DeltaTime;
		countedframes++;
	}
	else { countedframes++; }

	sec += Timer_DeltaTime;
	fps = countedframes / (sec / 1000.0);
	sec = sec > 1000 ? 0 : sec;
	countedframes = sec == 0 ? 0 : countedframes;

	//std::cout << TARGET_DeltaTime - Timer_DeltaTime << "\n";

	//fps = 1000.0 / (SDL_GetTicks64() - Timer_LastTime); // f/s = d | s*d = f | f*d = s = 1 (f helyesebb ugy hogy frame time)

	Timer_LastTime = SDL_GetTicks64();
	//std::cout << fps << " " << Timer_DeltaTime << "\n";
}