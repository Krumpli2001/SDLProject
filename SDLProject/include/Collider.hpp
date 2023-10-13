#pragma once

#include <SDL.h>

#include "CollisionHandler.hpp"

class Collider
{
private:
	SDL_Rect Collider_Box;
	SDL_Rect Collider_Buffer;

public:
	inline SDL_Rect getBox() { return Collider_Box; }
	inline void setBuffer(int x, int y, int w, int h) { Collider_Buffer = { x,y,w,h }; }
	inline void setBox(int x, int y, int w, int h) { Collider_Box = { x - Collider_Buffer.x, y - Collider_Buffer.y, w - Collider_Buffer.w, h - Collider_Buffer.h }; }
	//inline bool CollideWithMap() { return CollisionHandler::GetInstance()->MapCollision(Collider_Box); }

};