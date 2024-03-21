#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

#include "Player.hpp"


class UI {
private:
	UI() {};

	double scale = 1;
	bool FpsShowing{};

	int php{};
	int mphp{};
	std::string str_hp;

	bool showInventory = false;

	bool klikkelhetoInventory = false;

	int collisionLayer{};

	int cx{};
	int cy{};
	int kameraX{};
	int kameraY{};
	int kepernyoX{};
	int kepernyoY{};

	SDL_Rect highlightUI = {};

	std::pair<Item*, int> transfer{ nullptr, 0 };

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

	/// <summary>
	/// inicializ�l�s
	/// </summary>
	void UIInit();

	/// <summary>
	/// friss�t�s
	/// </summary>
	void Update();

	/// <summary>
	/// kirajzol�s
	/// </summary>
	void Draw();


	/*void TextureReset();
	void Clean();*/

	/// <summary>
	/// be�ll�tja hogy kirajzoljuk-e az fps-t
	/// </summary>
	/// <param name="e">true/false</param>
	inline void setFpsShowing(bool e) { FpsShowing = e; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>mutatjuk-e az fps-t</returns>
	inline bool getFpsShowing() const { return FpsShowing; }

	/// <summary>
	/// ki van-e nyitva az inventory
	/// </summary>
	/// <param name="e">true/false</param>
	inline void setInventoryShowing(bool e) { showInventory = e; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>mutatva van-e az eg�sz inventory</returns>
	inline bool getInventoryShowing() const { return showInventory; }

	/// <summary>
	/// be�ll�tja a collision vektort
	/// </summary>
	/// <param name="i">a megfelel� vektor indexe</param>
	inline void setCollisionLayer(int i) { collisionLayer = i; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>az eg�r X poz�ci�ja a map szempontj�b�l</returns>
	inline int getkepernyoX() const { return kepernyoX; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>az eg�r X poz�ci�ja a map szempontj�b�l</returns>
	inline int getkepernyoY() const { return kepernyoY; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>a kijel�lt blokk n�nyzete</returns>
	inline SDL_Rect* getHLRp() { return &highlightUI; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>az "eg�rn�l" lev� item adatai</returns>
	inline std::pair<Item*, int>* getTransfer() { return &transfer; }
};