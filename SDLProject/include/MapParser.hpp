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
	std::map<std::string, GameMap*> MapParser_MapDict;

	bool Parse(std::string id, std::string source);
	Tileset ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, std::vector<Tileset> tilesets, int tilesize, int rowcount, int colcount);

public:
	inline static MapParser* GetInstance()
	{
		if (MapParser_Instance == nullptr)
		{
			MapParser_Instance = new MapParser();
		}
		return MapParser_Instance;
	}

	inline GameMap* getMap(std::string id) { return MapParser_MapDict[id]; }

	bool Load();
	void Clean();
};