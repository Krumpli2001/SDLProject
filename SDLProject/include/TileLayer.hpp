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
	/// egy darab blokk kirajzol�sa
	/// </summary>
	/// <param name="x">x koordin�ta</param>
	/// <param name="y">y koordin�ta</param>
	virtual void Render(int x, int y);

	///// <summary>
	///// egy kocka friss�t�se
	///// </summary>
	///// <param name="x"></param>
	///// <param name="y"></param>
	virtual void Update(int x, int y);

	/// <summary>
	/// tile layer t�rl�sefelszabad�t�sa
	/// </summary>
	virtual void Clean();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>az adott layer matrix�t</returns>
	inline std::vector<std::vector<int>>* getTileMap() { return &TileLayer_TileMap; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>tile m�rete</returns>
	inline int getTileSize() { return TileLayer_TileSize; }
	/// <summary>
	/// 
	/// </summary>
	/// <returns>a p�lya sorainak sz�ma</returns>
	inline int getRowCount() { return TileLayer_RowCount; }
	/// <summary>
	/// /
	/// </summary>
	/// <returns>a p�lya oszlopainak sz�ma</returns>
	inline int getColCount() { return TileLayer_ColCount; }

	//virtual inline std::vector<Tileset>* getTilesetVector() { return &TileLayer_TileSets; }

};