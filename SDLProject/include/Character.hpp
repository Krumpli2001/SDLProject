#pragma once

#include "GameObject.hpp"

class Character : public GameObject {
protected:
	std::string Character_Name;
public:
	inline Character(Properties* props) : GameObject(props) {}

	virtual void Draw() = 0;
	virtual void Update(Uint64 dt) = 0;
	virtual void Clean() = 0;
};