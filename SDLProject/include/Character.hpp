#pragma once

#include "GameObject.hpp"

class Character : public GameObject {
protected:
	std::string Character_Name;
public:
	inline Character(Properties* props) : GameObject(props) {}

	//kirajzolja az adott karaktert
	//virtual void Draw() = 0;

	//friss�ti az adott karaktert
	//virtual void Update(Uint64 dt) = 0;

	//t�rli/felszabad�tja az adott karaktert a mem�ri�b�l
	//virtual void Clean() = 0;

	//be�ll�tja az adott karakterre vonatkoz� gravit�ci�t
	//virtual void setGravity(double G) = 0;

	//visszaadja az adott karakterre vonatkoz� gravit�ci�t
	//virtual void* getInventory() = 0;

	//elmenti a gameObj (jelenleg player) inventory-�t
	//virtual void saveInventory() = 0;

	//beolvass� a gameObj (jelenleg player) inventory-�t
	//virtual void readInventory() = 0;

	//visszaadja a gameObj (jelenleg player) inventory-�ban kiv�lasztott helyet
	//virtual int getSelectedInventory() = 0;

	//be�ll�tja az adott karakter c�lpontj�t
	//virtual void setTarget(int X, int Y) = 0;

};