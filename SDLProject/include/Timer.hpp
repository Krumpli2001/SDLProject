#pragma once

#include <SDL.h>

class Timer
{
private:
	Timer() {};
	static Timer* Timer_Instance;
	Uint64 Timer_DeltaTime{}; //millisecbe van, 1 sec = 1000 ms
	Uint64 Timer_LastTime{};

	const double TARGET_FPS = 30;
	const double TARGET_DELTATIME = 1000 / TARGET_FPS;

	bool pressed = false;
	int pressedtimer = 0;

	Uint64 countedframes=0;
	Uint64 sec = 0;
	int fps = 0;
	bool fpslock = false;

	bool menu = false;
public:
	static inline Timer* GetInstance()
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
	inline void setmenu(bool e) { menu = e; }

	bool pressable(Uint64 time);
};