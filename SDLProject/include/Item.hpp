#pragma once

#include <iostream>

struct Tile {
	Tile(int TID, std::string TN, bool iT, uint64_t MT) : TileID(TID), TileName(TN), isTransparent(iT), MineTime(MT) {}
	int TileID;
	std::string TileName;
	//std::string LayerID;
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
	inline int getItemID() { return ItemID; }
	//virtual int getTileID() = 0;
};


class Tool : public Item
{
public:
	Tool(int ID, std::string name) : Item(ID, name) {}
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