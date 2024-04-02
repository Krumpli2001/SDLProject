#pragma once

#include "GameObject.hpp"

enum playerAniState {
	IsIdle,
	IsWalking,
	IsJumping,
	IsFalling,
	IsAttacking,
	IsWalkingAndAttacking,
};

class Character : public GameObject {
protected:
	std::string Character_Name;
	short aniState{};
public:
	inline Character(Properties* props) : GameObject(props) {}
	virtual void AnimationState() = 0;

};