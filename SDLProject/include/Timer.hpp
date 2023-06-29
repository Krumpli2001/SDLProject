#pragma once

const int TARGET_FPS = 60;
const int TARGET_DeltaTime = 1.5;

class Timer
{
private:
	Timer() {};
	static Timer* Timer_Instance;
	double Timer_DeltaTime;
	double Timer_LastTime;
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

};

