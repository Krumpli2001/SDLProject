#pragma once

//////////////////////////////THIS IS KINDA DEPRECATED//////////////////////////////

#include "Timer.hpp"
#include "Engine.hpp"

class FPSCounter
{
private:
	static FPSCounter* FPS_Instance;
	FPSCounter() {};

	double scale{};

public:
	static inline FPSCounter* GetInstance()
	{
		if (FPS_Instance == nullptr)
		{
			FPS_Instance = new FPSCounter();
		}
		return FPS_Instance;
	}

	void Update();
	void Draw();
	void Clean();
};

//////////////////////////////THIS IS KINDA DEPRECATED//////////////////////////////
