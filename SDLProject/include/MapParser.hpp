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

	//p�lyaadatok beolvas�sa
	bool Parse(std::string id, std::string source);

	//tileset beolvas�sa
	Tileset ParseTileset(TiXmlElement* xmlTileset);

	//tile layer beolvas�sa
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

	//game map visszat�r�t�se
	inline GameMap* getMap(std::string id) { return MapParser_GameMap; }

	//p�lya bet�lt�se
	bool Load(std::string palyanev);

	//t�rl�s/felszabad�t�s
	void Clean();
};