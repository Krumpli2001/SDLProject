#pragma once

#include <SDL_ttf.h>
#include <string>
#include "Timer.hpp"
#include "Engine.hpp"

class FPSCounter
{
private:
	static FPSCounter* FPS_Instance;
	FPSCounter() {};

	TTF_Font* font = TTF_OpenFont("assets/cambria.ttf", 12);
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* surfaceMessage = nullptr;
	SDL_Texture* Message = nullptr;
	SDL_Rect Message_rect{ 0,0,100,100 }; //create a rect
	

public:
	inline static FPSCounter* GetInstance()
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