#pragma once

#include <iostream>

class Item
{
protected:
	Item(int IID, std::string name) : ItemID(IID), name(name) {}
	int ItemID;
	std::string name;
public:
	inline int getItemID() { return ItemID; }
	virtual int getTileID() = 0;
};


class Tool : public Item
{
	int getTileID() { return -1; }
};

class Block : public Item
{
private:
	int TileID;
public:
	Block(int IID, std::string name, int TID) : Item(IID, name), TileID(TID) {}
	int getTileID() { return TileID; }
};