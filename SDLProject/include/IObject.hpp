#pragma once

class IObject {
private:
public:

	//ki�r�s
	virtual void Draw() = 0;

	//friss�t�s
	virtual void Update(Uint64 dt) = 0;

	//t�rl�s/felszabad�t�s
	virtual void Clean() = 0;
};