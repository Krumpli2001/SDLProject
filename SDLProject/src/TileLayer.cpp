#include "TileLayer.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, std::vector<std::vector<int>> tilemap, std::vector<Tileset>* tilesets) :
	TileLayer_TileSize(tilesize), TileLayer_ColCount(colcount), TileLayer_RowCount(rowcount), TileLayer_TileMap(tilemap), TileLayer_TileSets(*tilesets)
{}

void TileLayer::Render(int x, int y)
{

	int bal = x - 80 < 0 ? 0 : x - 80;
	int jobb = x + 80 > TileLayer_ColCount ? TileLayer_ColCount : x + 80;
	int fel = y - 50 < 0 ? 0 : y - 50;
	int le = y + 50 > TileLayer_RowCount ? TileLayer_RowCount : y + 50;

	for (int i = fel; i < le; i++)
	{
		for (int j = bal; j < jobb; j++)
		{
			int tileID = TileLayer_TileMap[i][j];

			if (tileID != 0) {
				TextureManager::GetInstance()->DrawTile("texture_map", Engine::GetInstance()->getTileSize(), j * Engine::GetInstance()->getTileSize(), i * Engine::GetInstance()->getTileSize(), tileID / (TextureManager::GetInstance()->getTextureMap()->find("texture_map")->second.second.w / TileLayer_TileSize), tileID - 1);
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
