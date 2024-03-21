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
	/// inicializálás
	/// </summary>
	void UIInit();

	/// <summary>
	/// frissítés
	/// </summary>
	void Update();

	/// <summary>
	/// kirajzolás
	/// </summary>
	void Draw();


	/*void TextureReset();
	void Clean();*/

	/// <summary>
	/// beállítja hogy kirajzoljuk-e az fps-t
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
	/// <returns>mutatva van-e az egész inventory</returns>
	inline bool getInventoryShowing() const { return showInventory; }

	/// <summary>
	/// beállítja a collision vektort
	/// </summary>
	/// <param name="i">a megfelelõ vektor indexe</param>
	inline void setCollisionLayer(int i) { collisionLayer = i; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>az egér X pozíciója a map szempontjából</returns>
	inline int getkepernyoX() const { return kepernyoX; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>az egér X pozíciója a map szempontjából</returns>
	inline int getkepernyoY() const { return kepernyoY; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>a kijelölt blokk nényzete</returns>
	inline SDL_Rect* getHLRp() { return &highlightUI; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>az "egérnél" levõ item adatai</returns>
	inline std::pair<Item*, int>* getTransfer() { return &transfer; }
};