#include "Timer.hpp"
#include <iostream>
//#include <Windows.h>
#include <thread>
#include <chrono>

Timer* Timer::Timer_Instance = nullptr;

void Timer::getTick()
{
	Timer_DeltaTime = (SDL_GetTicks64() - Timer_LastTime); // *(TARGET_FPS / 1000.0);


	if ((Timer_DeltaTime < TARGET_DeltaTime) and fpslock) {
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(TARGET_DeltaTime - Timer_DeltaTime)));
		//Sleep(TARGET_DeltaTime - Timer_DeltaTime);
		Timer_DeltaTime = TARGET_DeltaTime;
	}

	fps = 1000.0 / (SDL_GetTicks64() - Timer_LastTime); // f/s = d | s*d = f | f*d = s = 1 (f helyesebb ugy hogy frame time)

	/*if (Timer_DeltaTime > TARGET_DeltaTime)
	{
		Timer_DeltaTime = TARGET_DeltaTime;
	}*/

	Timer_LastTime = SDL_GetTicks64();
	//std::cout << fps << " " << Timer_DeltaTime << "\n";
}

void Timer::sleep(long long ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
