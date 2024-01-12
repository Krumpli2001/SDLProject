#include <iostream>

class Item
{
protected:
	int ItemID;
	std::string ItemTextureID;
};

class Tool : public Item
{

};

class Block : public Item
{

};