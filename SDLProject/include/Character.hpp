#pragma once

#include "GameObject.hpp"

class Character : public GameObject {
protected:
	std::string Character_Name;
public:
	inline Character(Properties* props) : GameObject(props) {}

};