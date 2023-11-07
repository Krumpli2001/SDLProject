#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <Engine.hpp>

class Menu;

struct rublika {

	const char* szoveg;
	SDL_Rect doboz;
	SDL_Surface* surfaceMessage{};
	SDL_Texture* Message{};
	SDL_Color color;// = { 255,255,255 };
	TTF_Font* font = TTF_OpenFont("assets/cambria.ttf", 12);
	int szoveghossz{};
	bool isHighlighted = false;


	rublika(const char* sz, int x, int y, int w, int h, SDL_Color c) {
		doboz.x = x; doboz.y = y; doboz.w = w; doboz.h = h; szoveg = sz; color = c;
	}

	inline void letrehoz() {
		surfaceMessage = TTF_RenderText_Solid(font, szoveg, color);
		Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), surfaceMessage);
	}

	inline void setRectLocation(int x, int y) { doboz.x = x; doboz.y = y; }
};

class Menu
{
private:
	Menu() {};

	static Menu* Menu_Instance;
	std::unordered_map<std::string, SDL_Color> colors;
	std::vector<rublika> rublikak;
	std::vector<int> options;
	int highLighted = 0;
	int index = 0;
	bool eger = true;
	int cx = -1;
	int cy = -1;
	bool enter = false;

	bool ResetFlag = false;

	bool Main = false;
	bool GameOver = false;
	bool Title = true;
	//double menuScale{};

public:
	inline static Menu* GetInstance()
	{
		if (Menu_Instance == nullptr)
		{
			Menu_Instance = new Menu();
		}
		return Menu_Instance;
	}

	void MenuInit();
	void Update();
	void Draw();
	void Clean();
	void Reset();
	void doelse(std::string str, int index);

	void fillColorMap(std::string source);
	inline SDL_Color getColor(std::string color) { return colors[color]; }
	void setHighlighted(int i);
	inline void setEnter(bool e) { enter = e; }
	inline void setMain(bool e) { Main = e; }
	inline void setGameOver(bool e) { GameOver = e; }

	inline void getIndex(const char* str, int* index) {
		int i = 0;
		for (i; i < rublikak.size(); i++) {
			if (rublikak[i].szoveg == str) {
				*index = i;
				break;
			}
		}
	}
	inline bool melyik(const char* str, int* index) {
		getIndex(str, index);
		//options.push_back(i);
		if ((cx >= rublikak[*index].doboz.x and cy > rublikak[*index].doboz.y
			and cx <= rublikak[*index].doboz.w + rublikak[*index].doboz.x and
			cy <= rublikak[*index].doboz.h + rublikak[*index].doboz.y) and eger or rublikak[*index].isHighlighted) {
			return str;
		}
		else { return false; }
	}

	inline void RUpdate(std::string str, int index) {
		rublikak[index].color = getColor(str);
		rublikak[index].letrehoz();
		highLighted = index;
	}

	//ellenorzes miatt van itt
	/*inline void print_map(const std::unordered_map<std::string, SDL_Color>& m)
	{
		for (const auto& value : m) {
			std::cout << value.first << "\t\t";
			std::cout << static_cast<int>(value.second.r) << "\t";
			std::cout << static_cast<int>(value.second.g) << "\t";
			std::cout << static_cast<int>(value.second.b) << std::endl;
		}
		std::cout<<std::endl;
	}*/
};


/*
#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <unordered_map>
#include <Engine.hpp>

class Menu;

struct rublika {
	const char* szoveg;
	SDL_Rect doboz;
	SDL_Surface* surfaceMessage{};
	SDL_Texture* Message{};
	SDL_Color color = { 255,255,255 };
	TTF_Font* font = TTF_OpenFont("assets/cambria.ttf", 12);
	int szoveghossz{};
	bool isHighlighted = false;

	rublika() {}
	rublika(const char* sz, int x, int y, int w, int h) {
		doboz.x = x; doboz.y = y; doboz.w = w; doboz.h = h; szoveg = sz;
	}

	inline void letrehoz() {
		surfaceMessage = TTF_RenderText_Solid(font, szoveg, color);
		Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), surfaceMessage);
	}
};

class Menu
{
private:
	Menu() {};
	Menu(const Menu&) = delete;
	Menu operator = (const Menu&) = delete;

	static Menu* Menu_Instance;
	std::map<std::string, SDL_Color> colors;
	std::vector < std::pair<std::string, rublika> > rublikak;
	int highLighted{};
	bool eger = true;
	//std::unordered_map<std::string, rublika> rublikak;
	//std::unordered_map<std::string, rublika>::iterator highLighted{};
	int cx = -1;
	int cy = -1;
	bool enter = false;

	bool Main = true;

	void fillColorMap(std::string source);
	inline SDL_Color getColor(std::string color) { return colors[color]; }

public:
	inline static Menu* GetInstance()
	{
		if (Menu_Instance == nullptr)
		{
			Menu_Instance = new Menu();
		}
		return Menu_Instance;
	}

	void MenuInit();
	void Update();
	void Draw();
	void Clean();

	void setHighlighted(int i);
	void setEnter() { enter = true; }

	inline bool melyik(std::string s, int* x){
		int index = 0;
		for (int i = 0; i < rublikak.size(); i++) {
			if (rublikak[i].first == s) { index = i; break; }
		}
		if ((cx >= rublikak[index].second.doboz.x and cy > rublikak[index].second.doboz.y
			and cx <= rublikak[index].second.doboz.w + rublikak[index].second.doboz.x and cy
			<= rublikak[index].second.doboz.h + rublikak[index].second.doboz.y) and eger or rublikak[index].second.isHighlighted) {
			*x = index;
			return true;
		}
		return false;
	}

	//ellenorzes miatt van itt
	inline void print_map(const std::map<std::string, SDL_Color>& m)
	{
		for (const auto& value : m) {
			std::cout << value.first << "\t\t";
			std::cout << static_cast<int>(value.second.r) << "\t";
			std::cout << static_cast<int>(value.second.g) << "\t";
			std::cout << static_cast<int>(value.second.b) << std::endl;
		}
		std::cout << std::endl;
	}
};
*/