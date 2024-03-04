#pragma once

#include <iostream>

struct Tile {
	Tile(int TID, std::string TN, std::string LID, bool iT, uint64_t MT) : TileID(TID), TileName(TN), LayerID(LID), isTransparent(iT), MineTime(MT) {}
	int TileID;
	std::string TileName;
	std::string LayerID;
	bool isTransparent;
	uint64_t MineTime;
};

class Item
{
protected:
	Item(int IID, std::string name) : ItemID(IID), name(name) {}
	int ItemID;
	std::string name;
public:

	//item ID visszatérítése
	inline int getItemID() { return ItemID; }
	//virtual int getTileID() = 0;
};


class Tool : public Item
{
public:
	Tool(int ID, std::string name) : Item(ID, name) {}

	//nothing
	int getTileID() { return -1; }
};

class Block : public Item
{
private:
	//int TileID;
public:
	Block(int IID, std::string name) : Item(IID, name) {}
	//int getTileID() { return TileID; }
};