#pragma once

#include <SDL.h>

#include "FPSCounter.hpp"
#include "TextureManager.hpp"

class UI {
private:
	UI() {};

	double scale{};
	bool FpsShowing{};
public:
	inline static UI* GetInstance()
	{
		static UI* RNG_Instance;
		if (RNG_Instance == nullptr)
		{
			RNG_Instance = new UI();
			srand(time(0));
		}
		return RNG_Instance;
	}

	void Update();
	void Draw();
	void Clean();
	inline void setFpsShowing(bool e) { FpsShowing = e; }
	inline bool getFpsShowing() { return FpsShowing; }
};