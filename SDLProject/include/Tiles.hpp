#pragma once

#include <iostream>
#include <array>
#include <map>

	/**********************************************************************/
	enum TileIDs {
		semmi,
		fu,
		pirosvirag,
		fehervirag,
		b_eg,
		b_ko,
		b_felho,
		balrafu,
		fuvesfold,
		jobbrafu,
		fold,
		fublock,
		viz,
	};

	//std::array attetszo = {semmi, viz};

	/**********************************************************************/


	struct Tile {
		Tile(int TID, int LID, bool iT) : TileID(TID), LayerID(LID), isTransparent(iT) {}
		int TileID;
		int LayerID;
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