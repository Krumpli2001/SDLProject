#pragma once

#include <SDL.h>

const double TARGET_FPS = 60;
const double TARGET_DeltaTime = 16.67;

class Timer
{
private:
	Timer() {};
	static Timer* Timer_Instance;
	double Timer_DeltaTime;
	double Timer_LastTime;
	int fps;
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
	inline double getTimer_DeltaTime() { return Timer_DeltaTime; }
	inline int getFPS() { return fps; }

};

