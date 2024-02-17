#pragma once

#include <iostream>
#include <map>

	struct Tile {
		Tile(int TID, std::string TN, std::string LID, bool iT, uint64_t MT) : TileID(TID), TileName(TN), LayerID(LID), isTransparent(iT), MineTime(MT) {}
		int TileID;
		std::string TileName;
		std::string LayerID;
		bool isTransparent;
		uint64_t MineTime;
	};

	class TileData
	{
	private:

		TileData(){}
		std::map<int, Tile*> IData;
		std::map<std::string, Tile*> SData;

	public:

		TileData(const TileData&) = delete;

		inline static TileData* GetInstance()
		{
			static TileData* TileData_Instance;
			if (TileData_Instance == nullptr)
			{
				TileData_Instance = new TileData();
			}
			return TileData_Instance;
		}

		//return the tileData map with integers being the keys
		inline std::map<int, Tile*>* getTileIData() { return &IData; }
		//return the tileData map with strings being the keys
		inline std::map<std::string, Tile*>* getTileSData() { return &SData; }
		std::string getTileNameFromID(int key);
		int getTileIDFromName(std::string key);
		Tile* getTileDataFromID(int ID);
		Tile* getTileDataFromName(std::string str);

		bool parseTileData(std::string source);
		void ClearData();
	};