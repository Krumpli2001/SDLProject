#pragma once

//////////////////////////////THIS IS KINDA DEPRECATED//////////////////////////////

#include "Engine.hpp"
#include "Timer.hpp"

class FPSCounter
{
private:
	static FPSCounter* FPS_Instance;
	FPSCounter() {};
	double scale{};

public:
	static inline FPSCounter* GetInstance(bool del = false)
	{
		if (del) {
			if (FPS_Instance) {
				delete FPS_Instance;
			}
			FPS_Instance = nullptr;
			return nullptr;
		}
		if (FPS_Instance == nullptr)
		{
			FPS_Instance = new FPSCounter();
		}
		return FPS_Instance;
	}

	void Update();

	//fps szám kiírása
	void Draw();

	//void Clean();
};

//////////////////////////////THIS IS KINDA DEPRECATED//////////////////////////////
