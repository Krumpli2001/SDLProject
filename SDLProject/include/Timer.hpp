#pragma once

#include <SDL.h>

const double TARGET_FPS = 60;
const double TARGET_DeltaTime = 1000/ TARGET_FPS;

class Timer
{
private:
	Timer() {};
	static Timer* Timer_Instance;
	Uint64 Timer_DeltaTime{}; //millisecbe van, 1 sec = 1000 ms
	Uint64 Timer_LastTime{};
	int fps{};
public:
	inline static Timer* GetInstance()
	{
		if (Timer_Instance == nullptr)
		{
			Timer_Instance = new Timer();
		}
		return Timer_Instance;
	}

	void getTick();
	inline Uint64 getTimer_DeltaTime() { return Timer_DeltaTime; }
	inline int getFPS() { return fps; }
	bool fpslock = false;

};