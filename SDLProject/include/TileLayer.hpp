#pragma once

#include <string>
#include <vector>

#include "Layer.hpp"

struct Tileset {
	int FirstID{};
	int LastID{};
	int RowCount{};
	int ColCount{};
	int TileCount{};
	int TileSize{};
	std::string Name;
	std::string Source;
};

class TileLayer : public Layer
{
private:
	int TileLayer_TileSize;
	int TileLayer_RowCount;
	int TileLayer_ColCount;
	std::vector<std::vector<int>> TileLayer_TileMap;
	std::vector<Tileset> TileLayer_TileSets;
public:
	TileLayer(int tilesize, int rowcount, int colcount, std::vector<std::vector<int>> tilemap, std::vector<Tileset>* tilesets);

	/// <summary>
	/// egy darab blokk kirajzolása
	/// </summary>
	/// <param name="x">x koordináta</param>
	/// <param name="y">y koordináta</param>
	virtual void Render(int x, int y);

	///// <summary>
	///// egy kocka frissítése
	///// </summary>
	///// <param name="x"></param>
	///// <param name="y"></param>
	virtual void Update(int x, int y);

	/// <summary>
	/// tile layer törlésefelszabadítása
	/// </summary>
	virtual void Clean();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>az adott layer matrixát</returns>
	inline std::vector<std::vector<int>>* getTileMap() { return &TileLayer_TileMap; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>tile mérete</returns>
	inline int getTileSize() { return TileLayer_TileSize; }
	/// <summary>
	/// 
	/// </summary>
	/// <returns>a pálya sorainak száma</returns>
	inline int getRowCount() { return TileLayer_RowCount; }
	/// <summary>
	/// /
	/// </summary>
	/// <returns>a pálya oszlopainak száma</returns>
	inline int getColCount() { return TileLayer_ColCount; }

	//virtual inline std::vector<Tileset>* getTilesetVector() { return &TileLayer_TileSets; }

};