#pragma once

#include "Character.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"

class Enemy : public Character
{
private:
	Collider* Enemy_Collider;
	RigidBody* Enemy_RigidBody;
	Vector2D Enemy_LastSafePosition;

public:
	Enemy(Properties* props);

	virtual void Update(Uint64 dt);
	virtual void Draw();
	virtual void Clean();
};

