#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "FPSCounter.hpp"
#include "TextureManager.hpp"

class UI {
private:
	UI() {};

	double scale{};
	bool FpsShowing{};

	//ezek szovegnek kellenek - itt a hp-t szamba kiirni
	TTF_Font* font = TTF_OpenFont("assets/cambria.ttf", 12);
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* surfaceMessage = nullptr;
	SDL_Texture* Message = nullptr;
	SDL_Rect Message_rect{ 0,0,100 * static_cast<int>(Engine::GetInstance()->getTScale()), 100 * static_cast<int>(Engine::GetInstance()->getTScale()) };

	int php{};
	int mphp{};


public:
	inline static UI* GetInstance()
	{
		static UI* UI_Instance;
		if (UI_Instance == nullptr)
		{
			UI_Instance = new UI();
		}
		return UI_Instance;
	}

	void Update();
	void Draw();
	void Clean();
	inline void setFpsShowing(bool e) { FpsShowing = e; }
	inline bool getFpsShowing() { return FpsShowing; }
};