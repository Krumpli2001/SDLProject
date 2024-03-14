#pragma once

#include <SDL.h>

#include "CollisionHandler.hpp"

class Collider
{
private:
	SDL_Rect Collider_Box;
	int tilesize = CollisionHandler::GetInstance()->getTileSize();
public:

	//visszaadja a collider mereteit {x, y, w, h}
	inline SDL_Rect* getBox() { return &Collider_Box; }

	/*beállítja a collider méreteit
	x, y = felsõ bal sarok
	w, h = alsó jobb sarok*/ 
	inline void setBox(int x, int y, int w, int h) { 
		Collider_Box = { x, y, w, h };
	}
};