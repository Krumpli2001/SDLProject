#pragma once

#include <map>

#include "Item.hpp"

class ItemData {
private:

	ItemData() {}
	std::map<int, Item*> IData;
	std::map<std::string, Item*> SData;
	std::map<int, Item*> TIDData;

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

	bool ParseItemData(std::string src);
	void ClearData();
	inline Item* getItemByID(int id) { return IData.find(id)->second; }
	inline Item* getItemByName(std::string name) { return SData.find(name)->second; }
	inline Item* getItemByTileID(int id) { return TIDData.find(id)->second; }
};