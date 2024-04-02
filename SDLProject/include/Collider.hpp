#pragma once

#include <SDL.h>

#include "CollisionHandler.hpp"

class Collider
{
private:
	SDL_Rect Collider_Box;
	int tilesize = CollisionHandler::GetInstance()->getTileSize();
	std::vector<std::pair<int, int>> koords;
public:
	Collider() {};
	Collider(int w, int h) {
		//felso oldal
		int X = 0;
		while (X < w) {
			koords.push_back(std::make_pair(X, 0));
			X += tilesize;
		}
		koords.push_back(std::make_pair(w, 0));

		//also oldal
		X = 0;
		while (X < w) {
			koords.push_back(std::make_pair(X, h));
			X += tilesize;
		}
		koords.push_back(std::make_pair(w, h));

		//bal oldal
		int Y = tilesize;
		while (Y < h) {
			koords.push_back(std::make_pair(0, Y));
			Y += tilesize;
		}
		koords.push_back(std::make_pair(0, h));

		//jobb oldal
		Y = 0;
		while (Y < h) {
			koords.push_back(std::make_pair(w, Y));
			Y += tilesize;
		}
		//koords.push_back(std::make_pair(w, h)); nem kell, ketszer lenne
	}

	//visszaadja a collider mereteit {x, y, w, h}
	inline SDL_Rect* getBox() { return &Collider_Box; }

	/*beállítja a collider méreteit
	x, y = felsõ bal sarok
	w, h = alsó jobb sarok*/ 
	inline void setBox(int x, int y, int w, int h) { 
		Collider_Box = { x, y, w, h };
	}
};