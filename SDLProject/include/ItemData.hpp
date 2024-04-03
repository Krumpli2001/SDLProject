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
	inline static ItemData* GetInstance(bool del = false)
	{
		static ItemData* ItemData_Instance;
		if (del) {
			if (ItemData_Instance) {
				delete ItemData_Instance;
			}
			ItemData_Instance = nullptr;
			return nullptr;
		}
		if (ItemData_Instance == nullptr)
		{
			ItemData_Instance = new ItemData();
		}
		return ItemData_Instance;
	}

	//item adatok beolvas�sa, t�rol�sa f�jlb�l
	bool ParseData(std::string src);

	//t�rl�s/felszabad�t�s
	void ClearData();

	//minden tile item, de nem minden item tile

	//item visszaad�sa az ID-je alapj�n
	inline Item* getItemByID(int id) { return int_ItemData.find(id)->second; }

	//item visszaad�sa a neve alapj�n
	inline Item* getItemByName(std::string name) { return string_ItemData.find(name)->second; }

	//visszaadja tilemapot int kulccsal
	inline std::map<int, Tile*>* getTileDataByID() { return &int_TileData; }

	//visszaadja a tilemapot string kulccsal
	inline std::map<std::string, Tile*>* getTileDataByName() { return &string_TileData; }

	//visszaadja az adott tile nevet ID alapj�n
	std::string getTileNameFromID(int key);

	//visszaadja az ID-t nev alapj�n
	int getTileIDFromName(std::string key);

	//visszaadja a tile-t ID alapj�n
	Tile* getTileDataFromID(int ID);

	//visszaadja a tile-t nev alapj�n
	Tile* getTileDataFromName(std::string str);

	//bool parseTileData(std::string source);
	//void ClearData();
};