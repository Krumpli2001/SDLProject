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

	//checkolja hogy egy entety érintkezik-e a pályával
	bool MapCollision(GameObject* g, bool* grounded = nullptr);

	//viszsaad egy pointert ami a collision layer-re mutat (std::vector<std::vector<int>>*)
	//tehát az egész pályának a tile adatait tartalmazza
	inline std::vector<std::vector<int>>* getCollisionTileMap() { return CollisionHandler_CollitionTileMap; }

	//visstaadja hogy a pályán mekkora egy négyzet
	inline int getTileSize() { return tileSize; }

	//visstaadja a collision tilelayert, ebbe beletartozik a palya matrixa (amit a getCollisionTileMap() ad vissza)
	//de emellett még tartalmazza a pálya méreteit is
	inline TileLayer* getCollisionLayer() { return CollisionHandler_CollisionLayer; }

	//reseteli a collision layert valtozás esetén, pl. új pálya betöltése esetén
	void reset();

	std::vector<int>* getAttetszo() { return &attetszo; }
};