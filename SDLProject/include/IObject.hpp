#pragma once

class IObject {
private:
public:

	//kiírás
	virtual void Draw() = 0;

	//frissítés
	virtual void Update(Uint64 dt) = 0;

	//törlés/felszabadítás
	virtual void Clean() = 0;
};