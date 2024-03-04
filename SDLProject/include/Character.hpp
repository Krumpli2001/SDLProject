#pragma once

#include "GameObject.hpp"

class Character : public GameObject {
protected:
	std::string Character_Name;
public:
	inline Character(Properties* props) : GameObject(props) {}

	//kirajzolja az adott karaktert
	//virtual void Draw() = 0;

	//frissíti az adott karaktert
	//virtual void Update(Uint64 dt) = 0;

	//törli/felszabadítja az adott karaktert a memóriából
	//virtual void Clean() = 0;

	//beállítja az adott karakterre vonatkozó gravitációt
	//virtual void setGravity(double G) = 0;

	//visszaadja az adott karakterre vonatkozó gravitációt
	//virtual void* getInventory() = 0;

	//elmenti a gameObj (jelenleg player) inventory-át
	//virtual void saveInventory() = 0;

	//beolvassá a gameObj (jelenleg player) inventory-át
	//virtual void readInventory() = 0;

	//visszaadja a gameObj (jelenleg player) inventory-ában kiválasztott helyet
	//virtual int getSelectedInventory() = 0;

	//beállítja az adott karakter célpontját
	//virtual void setTarget(int X, int Y) = 0;

};