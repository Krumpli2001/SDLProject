#pragma once

#include <map>

#include "Item.hpp"

class ItemData {
private:

	ItemData() {}
	std::map<int, Item*> int_ItemData;
	std::map<std::string, Item*> string_ItemData;

	std::map<int, Tile*> int_TileData;
	std::map<std::string, Tile*> string_TileData;

public:

	ItemData(const ItemData&) = delete;
	inline static ItemData* GetInstance()
	{
		static ItemData* ItemData_Instance;
		if (ItemData_Instance == nullptr)
		{
			ItemData_Instance = new ItemData();
		}
		return ItemData_Instance;
	}

	bool ParseData(std::string src);
	void ClearData();
	inline Item* getItemByID(int id) { return int_ItemData.find(id)->second; }
	inline Item* getItemByName(std::string name) { return string_ItemData.find(name)->second; }

	inline std::map<int, Tile*>* getTileDataByID() { return &int_TileData; }
	inline std::map<std::string, Tile*>* getTileDataByName() { return &string_TileData; }
	std::string getTileNameFromID(int key);
	int getTileIDFromName(std::string key);
	Tile* getTileDataFromID(int ID);
	Tile* getTileDataFromName(std::string str);

	//bool parseTileData(std::string source);
	//void ClearData();
};