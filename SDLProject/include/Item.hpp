#pragma once

#include <iostream>

struct Tile {
	Tile(int TID, const std::string& TN, const std::string& LID, bool iT, uint32_t MT, int MS) : TileID(TID), TileName(TN), LayerID(LID), isTransparent(iT), MineTime(MT), MaxStack(MS) {}
	int TileID;
	std::string TileName;
	std::string LayerID;
	bool isTransparent;
	uint32_t MineTime;
	int MaxStack;
};

enum tipus {
	tool,
	block,
};

class Item
{
protected:
	Item(int IID, const std::string& name, int MS) : ItemID(IID), name(name), MaxStack(MS) {}
	int ItemID;
	std::string name;
	int MaxStack;
	short type{};
public:

	//item ID visszatérítése
	inline int getItemID() { return ItemID; }
	inline std::string* getName() { return &name; }
	virtual short getType() = 0;
};


class Tool : public Item
{
private:
	int AttackPower{};
	int Heal{};
	bool Consumable{};
public:
	inline Tool(int ID, const std::string& name, int attack, int heal, bool Cons,  int MS) : Item(ID, name, MS), AttackPower(attack), Heal(heal), Consumable(Cons) {}

	//nothing
	inline int getTileID() { return -1; }
	inline int getAttackPower() { return AttackPower; }
	inline int getHealing() { return Heal; }
	inline short getType() override { return tipus::tool; }
	inline bool getCons() { return Consumable; }
};

class Block : public Item
{
private:
	//int TileID;
public:
	inline Block(int IID, const std::string& name, int MS) : Item(IID, name, MS) {}
	inline short getType() override { return tipus::block; }
};