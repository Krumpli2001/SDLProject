#include "TileLayer.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, std::vector<std::vector<int>> tilemap, std::vector<Tileset>* tilesets) :
	TileLayer_TileSize(tilesize), TileLayer_ColCount(colcount), TileLayer_RowCount(rowcount), TileLayer_TileMap(tilemap), TileLayer_TileSets(*tilesets)
{}

void TileLayer::Render(int x, int y)
{

	int bal = x - 100 < 0 ? 0 : x - 100;
	int jobb = x + 100 > TileLayer_ColCount ? TileLayer_ColCount : x + 100;
	int fel = y - 75 < 0 ? 0 : y - 75;
	int le = y + 75 > TileLayer_RowCount ? TileLayer_RowCount : y + 75;

	for (int i = fel; i < le; i++)
	{
		for (int j = bal; j < jobb; j++)
		{
			int tileID = TileLayer_TileMap[i][j];

			if (tileID != 0) {
				TextureManager::GetInstance()->DrawTile("texture_map", Engine::GetInstance()->getTileSize(), j * Engine::GetInstance()->getTileSize(), i * Engine::GetInstance()->getTileSize(), 0, tileID - 1);
			}
		}
	}
}

void TileLayer::Update(int x, int y)
{

}

void TileLayer::Clean()
{
	for (int i = 0; i < TileLayer_TileMap.size(); i++) {
		TileLayer_TileMap[i].clear();
	}
	TileLayer_TileMap.clear();
	TileLayer_TileSets.clear();
}
