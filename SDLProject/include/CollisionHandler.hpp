#pragma once

#include <vector>
#include <SDL.h>

#include "ItemData.hpp"
#include "TileLayer.hpp"

class GameObject; //öszinten nem tudom miert mukodik az elore deklaralas

class CollisionHandler
{
private:
	CollisionHandler();
	static CollisionHandler* CollisionHandler_Instance;
	std::vector<std::vector<int>>* CollisionHandler_CollitionTileMap;
	TileLayer* CollisionHandler_CollisionLayer;

	std::vector<int> attetszo;

	int tileSize;
	int rowCount;
	int colCount;
public:

	static inline CollisionHandler* GetInstance()
	{
		if (CollisionHandler_Instance == nullptr)
		{
			CollisionHandler_Instance = new CollisionHandler();
		}
		return CollisionHandler_Instance;
	}

	//checkolja 2 entity kozotti atfedest
	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	//checkolja hogy egy enteti erintkezik e a mappal
	bool MapCollision(GameObject* g, bool* grounded = nullptr);
	inline std::vector<std::vector<int>>* getCollisionTileMap() { return CollisionHandler_CollitionTileMap; }
	inline int getTileSize() { return tileSize; }
	inline TileLayer* getCollisionLayer() { return CollisionHandler_CollisionLayer; }
	void reset();
};