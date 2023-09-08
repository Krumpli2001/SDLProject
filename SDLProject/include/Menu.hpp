#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Input.hpp"
#include <Engine.hpp>

class Menu
{
private:
	Menu() {};

	static Menu* Menu_Instance;
	//SDL_Rect BG;
	TTF_Font* font = TTF_OpenFont("assets/cambria.ttf", 12);
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* surfaceMessage = nullptr;
	SDL_Texture* Message = nullptr;
	SDL_Rect Message_rect{ 0,0,1000,300 };

public:
	inline static Menu* GetInstance()
	{
		if (Menu_Instance == nullptr)
		{
			Menu_Instance = new Menu();
		}
		return Menu_Instance;
	}

	//inline SDL_Rect* getBG() { return &BG; }

	void Update();
	void Draw();
	void Clean();

};