#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
//#include "Input.hpp"
#include <Engine.hpp>

struct rublika
{
	const char* szoveg;
	SDL_Rect doboz;
	SDL_Surface* surfaceMessage{};
	SDL_Texture* Message{};
	int szoveghossz{};

	rublika(const char* sz, int x, int y, int w, int h, TTF_Font* f, SDL_Color c) {
		//szoveg = "sajt";
		doboz.x = x; doboz.y = y; doboz.w = w; doboz.h = h; szoveg = sz;
		surfaceMessage = TTF_RenderText_Solid(f, szoveg, c);
		Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surfaceMessage);
	}
};

class Menu
{
private:
	Menu() {};

	static Menu* Menu_Instance;
	//SDL_Rect BG;
	TTF_Font* font = TTF_OpenFont("assets/cambria.ttf", 12);
	SDL_Color color = { 255, 255, 255 };
	std::vector<rublika> rublikak;

	/*SDL_Surface* surfaceMessage = nullptr;
	SDL_Texture* Message = nullptr;
	SDL_Rect Message_rect{ 0,0,1000,300 };*/

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

	void MenuInit();
	void Update();
	void Draw();
	void Clean();

};