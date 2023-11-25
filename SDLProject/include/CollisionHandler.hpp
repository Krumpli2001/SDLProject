#pragma once

#include <vector>
#include <SDL.h>

#include "TileLayer.hpp"

class GameObject; //�szinten nem tudom miert mukodik az elore deklaralas

class CollisionHandler
{
private:
	CollisionHandler();
	static CollisionHandler* CollisionHandler_Instance;
	std::vector<std::vector<int>> CollisionHandler_CollitionTileMap;
public:
	TileLayer* CollisionHandler_CollisionLayer;

	static inline CollisionHandler* GetInstance()
	{
		if (CollisionHandler_Instance == nullptr)
		{
			CollisionHandler_Instance = new CollisionHandler();
		}
		return CollisionHandler_Instance;
	}

	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	bool MapCollision(GameObject* g);
	inline std::vector<std::vector<int>>* getCollisionTileMap() { return &CollisionHandler_CollitionTileMap; }
	void reset();
};