#pragma once

#include "Character.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "SpriteAnimation.hpp"
#include "ObjectFactory.hpp"

class Enemy : public Character
{
protected:
	Collider* Enemy_Collider;
	RigidBody* Enemy_RigidBody;
	Vector2D Enemy_LastSafePosition;

	SpriteAnimation* Enemy_SpriteAnimation;

public:
	Enemy(Properties* props);

	virtual void Update(Uint64 dt);
	virtual void Draw();
	virtual void Clean();
	inline void setGravity(double G) { Enemy_RigidBody->setRigidBody_Gravity(G); } 
	inline Collider* getCollider() { return Enemy_Collider; }
	inline bool isAttacking() { return false; }
	inline double getAttacktime() { return 0; }
	inline int getAttackPower() { return 0; }
	virtual void AnimationState() = 0;
};

class Zombie : public Enemy{
public:
	Zombie(Properties* props) : Enemy(props) {};
	virtual void AnimationState();
};

class Skeleton : public Enemy{
public:
	Skeleton(Properties* props) : Enemy(props) {};
	virtual void AnimationState();
};