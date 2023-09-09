#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <Engine.hpp>

class Menu;

struct rublika {
	//friend class Menu;

	const char* szoveg;
	SDL_Rect doboz;
	SDL_Surface* surfaceMessage{};
	SDL_Texture* Message{};
	SDL_Color color = {255,255,255};
	TTF_Font* font = TTF_OpenFont("assets/cambria.ttf", 12);
	int szoveghossz{};
	bool isHighlighted = false;

	rublika(const char* sz, int x, int y, int w, int h/*, TTF_Font* f*//*, SDL_Color c*/) {
		//szoveg = "sajt";
		doboz.x = x; doboz.y = y; doboz.w = w; doboz.h = h; szoveg = sz;// font = f;// color = c;
	}

	inline void letrehoz() {
		surfaceMessage = TTF_RenderText_Solid(font, szoveg, color);
		Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surfaceMessage);
	}
};

class Menu
{
private:
	Menu() {};

	static Menu* Menu_Instance;
	std::map<std::string, SDL_Color> colors;
	std::vector<rublika> rublikak;
	int highLighted = 0;
	int cx = -1;
	int cy = -1;
	bool enter = false;

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

	void fillColorMap(std::string source);
	inline SDL_Color getColor(std::string color) { return colors[color]; }
	void setHighlighted(int i);
	void setEnter() { enter = true; }

	//ellenorzes miatt van itt
	inline void print_map(const std::map<std::string, SDL_Color>& m)
	{
		for (const auto& value : m) {
			std::cout << value.first << "\t\t";
			std::cout << static_cast<int>(value.second.r) << "\t";
			std::cout << static_cast<int>(value.second.g) << "\t";
			std::cout << static_cast<int>(value.second.b) << std::endl;
		}
		std::cout<<std::endl;
	}
};