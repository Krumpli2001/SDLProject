#pragma once

#include <SDL.h>

const double TARGET_FPS = 60;
const double TARGET_DeltaTime = 1000 / TARGET_FPS;

class Timer
{
private:
	Timer() {};
	static Timer* Timer_Instance;
	Uint64 Timer_DeltaTime{}; //millisecbe van, 1 sec = 1000 ms
	Uint64 Timer_LastTime{};

	bool pressed = false;
	int pressedtimer = 0;

	double countedframes=0;
	double sec = 0;
	int fps{};
	bool fpslock = false;
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
	inline bool getFPSLock() { return fpslock; }
	inline void setFPSLock(bool e) { fpslock = e; }
	inline double getSec() { return sec; }
	inline bool getPressed() { return pressed; }

	bool pressable(Uint64 time);
};