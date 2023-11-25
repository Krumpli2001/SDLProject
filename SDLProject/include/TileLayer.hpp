#pragma once

#include <string>
#include <vector>

#include "Layer.hpp"

struct Tileset {
	int FirstID;
	int LastID;
	int RowCount;
	int ColCount;
	int TileCount;
	int TileSize;
	std::string Name;
	std::string Source;
};

class TileLayer : public Layer
{
private:
	int TileLayer_TileSize;
	int TileLayer_RowCount;
	int TileLayer_ColCount;
	std::vector<std::vector<int> > TileLayer_TileMap;
	std::vector<Tileset> TileLayer_TileSets;
public:
	TileLayer(int tilesize, int rowcount, int colcount, std::vector<std::vector<int> > tilemap, std::vector<Tileset> tilesets);
	virtual void Render(int x, int y);
	virtual void Update(int x, int y);
	virtual void Clean();
	inline std::vector<std::vector<int> > getTileMap() { return TileLayer_TileMap; }
	inline std::vector<Tileset> getTileSets() { return TileLayer_TileSets; }
	inline int getTileset() { return TileLayer_TileSets[0].ColCount; }

	inline int getTileSize() { return TileLayer_TileSize; }
	inline int getRowCount() { return TileLayer_RowCount; }
	inline int getColCount() { return TileLayer_ColCount; }

};