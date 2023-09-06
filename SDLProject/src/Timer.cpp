#include "Timer.hpp"
#include <iostream>


Timer* Timer::Timer_Instance = nullptr;

void Timer::getTick()
{
	Timer_DeltaTime = (SDL_GetTicks64() - Timer_LastTime) * (TARGET_FPS / 1000.0);

	fps = 1000.0 / (SDL_GetTicks64() - Timer_LastTime);

	if (Timer_DeltaTime > TARGET_DeltaTime)
	{
		Timer_DeltaTime = TARGET_DeltaTime;
	}

	Timer_LastTime = SDL_GetTicks64();
	//std::cout << Timer_DeltaTime << "\n";
}
