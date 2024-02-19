#pragma once

#include <map>

#include "Item.hpp"

class ItemData {
private:

	ItemData() {}
	std::map<int, Item*> int_ItemData;
	std::map<std::string, Item*> string_ItemData;
	//std::map<int, Item*> TIDData;

	std::map<int, Tile*> int_TileData;
	std::map<std::string, Tile*> string_TileData;

public:

	ItemData(const ItemData&) = delete;
	inline static ItemData* GetInstance()
	{
		static ItemData* ItemDataInstance;
		if (ItemDataInstance == nullptr)
		{
			ItemDataInstance = new ItemData();
		}
		return ItemDataInstance;
	}

	bool ParseData(std::string src);
	void ClearData();
	inline Item* getItemByID(int id) { return int_ItemData.find(id)->second; }
	inline Item* getItemByName(std::string name) { return string_ItemData.find(name)->second; }
	//inline Item* getItemByTileID(int id) { return TIDData.find(id)->second; }

	inline std::map<int, Tile*>* getTileDataByID() { return &int_TileData; }
	inline std::map<std::string, Tile*>* getTileDataByName() { return &string_TileData; }
	std::string getTileNameFromID(int key);
	int getTileIDFromName(std::string key);
	Tile* getTileDataFromID(int ID);
	Tile* getTileDataFromName(std::string str);

	//bool parseTileData(std::string source);
	//void ClearData();
};