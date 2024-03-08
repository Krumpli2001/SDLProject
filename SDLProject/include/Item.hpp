#pragma once

#include <iostream>

struct Tile {
	Tile(int TID, std::string TN, std::string LID, bool iT, uint64_t MT, int MS) : TileID(TID), TileName(TN), LayerID(LID), isTransparent(iT), MineTime(MT), MaxStack(MS) {}
	int TileID;
	std::string TileName;
	std::string LayerID;
	bool isTransparent;
	uint64_t MineTime;
	int MaxStack;
};

class Item
{
protected:
	Item(int IID, std::string name, int MS) : ItemID(IID), name(name), MaxStack(MS) {}
	int ItemID;
	std::string name;
	int MaxStack;
public:

	//item ID visszatérítése
	inline int getItemID() { return ItemID; }
	//virtual int getTileID() = 0;
};


class Tool : public Item
{
public:
	Tool(int ID, std::string name, int MS) : Item(ID, name, MS) {}

	//nothing
	int getTileID() { return -1; }
};

class Block : public Item
{
private:
	//int TileID;
public:
	Block(int IID, std::string name, int MS) : Item(IID, name, MS) {}
	//int getTileID() { return TileID; }
};