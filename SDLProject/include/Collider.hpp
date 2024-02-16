#pragma once

#include <SDL.h>

#include "CollisionHandler.hpp"

class Collider
{
private:
	SDL_Rect Collider_Box;

public:
	inline SDL_Rect* getBox() { return &Collider_Box; }
	inline void setBox(int x, int y, int w, int h) { Collider_Box = { x, y, w, h }; }
};