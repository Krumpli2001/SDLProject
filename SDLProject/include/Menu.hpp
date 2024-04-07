#pragma once

#include <filesystem>
#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>

#include "Engine.hpp"

class Menu;

struct rublika {

	int x, y, w, h;
	const char* szoveg;
	std::string color;
	bool isHighlighted = false;


	rublika(const char* SZ, int X, int Y, int H) : x(X), y(Y), h(H), szoveg(SZ) {
		//rublika::x = x; rublika::y = y; rublika::h = h; szoveg = sz;
	}

	//az adott t�glalap �thelyez�se
	inline void setRectLocation(int x, int y) { rublika::x = x; rublika::y = y; }
};

enum sub {
	Main,
	GameOver,
	Title,
	Settings,
	Load,
};

class Menu
{
private:
	Menu() {};

	static Menu* Menu_Instance;
	std::vector<rublika> rublikak;
	std::vector<int> options;
	std::vector<char*> saves;
	int highLighted = 0;
	int index = 0;
	bool eger = true;
	int cx = -1;
	int cy = -1;
	bool enter = false;
	bool ResetFlag = false;

	int submenu = sub::Title;
	int prevSubmenu = sub::Title;
	double menuScale{};

	std::string loaded_map_name;

	std::unordered_map<std::string, SDL_Color>* colors = TextureManager::GetInstance()->getColors();

public:
	static inline Menu* GetInstance(bool del = false)
	{
		if (del) {
			if (Menu_Instance) {
				delete Menu_Instance;
			}
			Menu_Instance = nullptr;
			return nullptr;
		}
		if (Menu_Instance == nullptr)
		{
			Menu_Instance = new Menu();
		}
		return Menu_Instance;
	}

	//inicializ�l�s
	void MenuInit();

	//friss�t�s
	void Update();

	//ki�r�s
	void Draw();

	//t�rl�s/felszabad�t�s
	void Clean();

	//reset
	void Reset();

	//az akt�v gomb kiv�laszt�s�nak kijel�l�se
	void setHighlighted(int i);

	//enter gomb be�ll�t�sa (highlight miatt)
	inline void setEnter(bool e) { enter = e; }

	//main menu be�ll�t�sa
	inline void setMain(bool e) { 
		if (e) { submenu = sub::Main; }
	}

	//game over menu be�ll�t�sa
	inline void setGameOver(bool e) { 
		if (e) { submenu = sub::GameOver; }
	}

	//index �ll�t�sa
	inline void getIndex(const char* str, int* index) {
		int i = 0;
		for (i; i < rublikak.size(); i++) {
			if (rublikak[i].szoveg == str) {
				*index = i;
				break;
			}
		}
	}

	//rublika kiv�laszt�sa (ak�r gombokkal ak�r eg�rrel)
	inline bool melyik(const char* str, int* index) {
		getIndex(str, index);
		auto scale = Engine::GetInstance()->getScale();
		if ((cx >= rublikak[*index].x and cy > rublikak[*index].y
			and cx <= rublikak[*index].w*scale + rublikak[*index].x and
			cy <= rublikak[*index].h + rublikak[*index].y) and eger or rublikak[*index].isHighlighted) {
			return true;
		}
		return false;
	}

	//csak siman kiirja a sort
	inline void doelse(const std::string& str, int index) {
		rublikak[index].color = str;
	}

	//kiirja es kivalasztja a highlight-ot
	inline void RUpdate(const std::string& str, int index) {
		rublikak[index].color = str;
		highLighted = index;
	}

	//ellenorzes miatt van itt - konzolra
	inline void print_map(const std::unordered_map<std::string, SDL_Color>& m)
	{
		for (const auto& value : m) {
			std::cout << value.first << "\t\t";
			std::cout << static_cast<int>(value.second.r) << "\t";
			std::cout << static_cast<int>(value.second.g) << "\t";
			std::cout << static_cast<int>(value.second.b) << std::endl;
		}
		std::cout<<std::endl;
	}

	//visszaadja az akt�v p�lya nev�t
	inline std::string* getMapName() { return &loaded_map_name; }
};
