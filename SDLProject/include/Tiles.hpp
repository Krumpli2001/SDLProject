#pragma once

#include <iostream>
#include <map>

	struct Tile {
		Tile(int TID, std::string LID, bool iT) : TileID(TID), LayerID(LID), isTransparent(iT) {}
		int TileID;
		std::string LayerID;
		bool isTransparent;
	};

	class TileData
	{
	private:

		TileData(){}
		std::map<std::string, Tile*> Data;

	public:

		TileData(const TileData&) = delete;

		inline static TileData* GetInstance()
		{
			static TileData* TileData_Instance;
			if (TileData_Instance == nullptr)
			{
				TileData_Instance = new TileData();
				srand(time(nullptr));
			}
			return TileData_Instance;
		}

		inline std::map<std::string, Tile*>* getTileData() { return &Data; }
		int getTileIdFromName(std::string key);
		bool parseTileData(std::string source);
		void ClearData();
	};