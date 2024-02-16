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

	void UIInit();
	void Update();
	void Draw();
	void TextureReset();
	void Clean();
	inline void setFpsShowing(bool e) { FpsShowing = e; }
	inline bool getFpsShowing() { return FpsShowing; }
	inline void setInventoryShowing(bool e) { showInventory = e; }
	inline bool getInventoryShowing() { return showInventory; }
	inline void setCollisionLayer(int i) { collisionLayer = i; }
	inline int getkepernyoX() { return kepernyoX; }
	inline int getkepernyoY() { return kepernyoY; }
	inline SDL_Rect* getHLRp() { return &highlightUI; }

	inline std::pair<Item*, int>* getTransfer() { return &transfer; }
};