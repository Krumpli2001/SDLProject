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
};


class Tool : public Item
{

};

class Block : public Item
{
private:
	int TileID;
public:
	Block(int IID, std::string name, std::string ITID, int TID) : Item(IID, name, ITID), TileID(TID) {}
};