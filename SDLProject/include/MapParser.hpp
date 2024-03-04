#pragma once

#include <map>
#include <tinyxml.h>

#include "GameMap.hpp"
#include "TileLayer.hpp"

class MapParser
{
private:
	MapParser() {};
	static MapParser* MapParser_Instance;
	GameMap* MapParser_GameMap;

	bool MapParsed = false;

	//pályaadatok beolvasása
	bool Parse(std::string id, std::string source);

	//tileset beolvasása
	Tileset ParseTileset(TiXmlElement* xmlTileset);

	//tile layer beolvasása
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, std::vector<Tileset>* tilesets, int tilesize, int rowcount, int colcount);

public:
	static inline MapParser* GetInstance()
	{
		if (MapParser_Instance == nullptr)
		{
			MapParser_Instance = new MapParser();
		}
		return MapParser_Instance;
	}

	//game map visszatérítése
	inline GameMap* getMap(std::string id) { return MapParser_GameMap; }

	//pálya betöltése
	bool Load(std::string palyanev);

	//törlés/felszabadítás
	void Clean();
};