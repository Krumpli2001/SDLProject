#include "TileLayer.hpp"
#include "TextureManager.hpp"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, std::vector<std::vector<int> > tilemap, std::vector<Tileset> tilesets) :
	TileLayer_TileSize(tilesize), TileLayer_ColCount(colcount), TileLayer_RowCount(rowcount), TileLayer_TileMap(tilemap), TileLayer_TileSets(tilesets)
{
	for (unsigned int i = 0; i < TileLayer_TileSets.size(); i++)
		{
			TextureManager::GetInstance()->Load(TileLayer_TileSets[i].Name, "assets/maps/" + TileLayer_TileSets[i].Source);
		}
}

void TileLayer::Render()
{
	for (unsigned int i = 0; i < TileLayer_RowCount; i++)
	{
		for (unsigned int j = 0; j < TileLayer_ColCount; j++)
		{
			int tileID = TileLayer_TileMap[i][j];

			if (tileID == 0)
			{
				continue;
			}
			else
			{
				int index = 0;
				if (TileLayer_TileSets.size() > 1)
				{
					for (unsigned int k = 1; k < TileLayer_TileSets.size(); k++)
					{
						if ((tileID >= TileLayer_TileSets[k].FirstID) and (tileID <= TileLayer_TileSets[k].LastID))
						{
							tileID = tileID + TileLayer_TileSets[k].TileCount - TileLayer_TileSets[k].LastID;
							index = k;
							break;
						}
					}
				}

				Tileset tileset = TileLayer_TileSets[index];
				int tilerow = tileID / tileset.ColCount;
				int tilecol = tileID - tilerow * tileset.ColCount - 1;

				if (tileID % tileset.ColCount == 0)
				{
					tilerow--;
					tilecol = tileset.ColCount - 1;
				}

				TextureManager::GetInstance()->DrawTile(tileset.Name, tileset.TileSize, j * tileset.TileSize, i * tileset.TileSize, tilerow, tilecol);

			}
		}
	}
}

void TileLayer::Update()
{

}