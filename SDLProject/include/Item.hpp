#include <iostream>

class Item
{
protected:
	int ItemID;
	std::string ItemTextureID;
public:
	Item(int IID, std::string ITID) : ItemID(IID), ItemTextureID(ITID) {}
	inline int getItemID() { return ItemID; }
	virtual ~Item() = 0;
};
Item::~Item(){}

class Tool : public Item
{

};

class Block : public Item
{
private:
	int TileID;
	uint64_t mineing_time;
public:
	Block(int IID, std::string ITID, int TID, uint64_t MT) : Item(IID, ITID), TileID(TID), mineing_time(MT) {}
};