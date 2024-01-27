#pragma once

#include <iostream>

class Item
{
protected:
	Item(int IID, std::string name, std::string ITID) : ItemID(IID), name(name), ItemTextureID(ITID) {}
	int ItemID;
	std::string name;
	std::string ItemTextureID;
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
	Block(int IID, std::string name, std::string ITID, int TID) : Item(IID, name, ITID), TileID(TID) {}
	int getTileID() { return TileID; }
};