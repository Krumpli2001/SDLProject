#pragma once

#include <iostream>
#include <map>

	struct Tile {
		Tile(std::string LID, bool iT) : LayerID(LID), isTransparent(iT) {}
		//std::string TileName;
		std::string LayerID;
		bool isTransparent;
	};

	class TileData
	{
	private:

		TileData(){}
		std::map<std::pair<int, std::string>, Tile*> Data;

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

		inline std::map<std::pair<int, std::string>, Tile*>* getTileData() { return &Data; }
		std::string getTileNameFromID(int key);
		int getTileIDFromName(std::string key);
		Tile* getTileDataFromID(int ID);
		Tile* getTileDataFromName(std::string str);
		bool parseTileData(std::string source);
		void ClearData();
	};