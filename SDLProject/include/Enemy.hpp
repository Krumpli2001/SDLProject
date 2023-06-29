#pragma once

#include "Character.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "SequentialAnimation.hpp"

class Enemy : public Character
{
private:
	Collider* Enemy_Collider;
	RigidBody* Enemy_RigidBody;
	SequentialAnimation* Enemy_SeqAnimation;
	Vector2D Enemy_LastSafePosition;

public:
	Enemy(Properties* props);

	virtual void Update(double dt);
	virtual void Draw();
	virtual void Clean();
};

