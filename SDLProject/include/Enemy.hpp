#pragma once

#include "Character.hpp"
#include "RigidBody.hpp"
#include "SpriteAnimation.hpp"
#include "ObjectFactory.hpp"
#include "Engine.hpp"

class Enemy : public Character
{
protected:
	Collider* Enemy_Collider;
	RigidBody* Enemy_RigidBody;
	Vector2D Enemy_LastSafePosition;

	SpriteAnimation* Enemy_SpriteAnimation;

	int Enemy_AttackPower{};

	int Enemy_TargetPosX{};
	int Enemy_TargetPosY{};

	bool fal = false;

	bool Enemy_IsGrounded = false;
	bool Enemy_IsJumping = false;
	Uint64 Enemy_JumpTime;

public:
	Enemy(Properties* props);

	virtual void Update(Uint64 dt);
	virtual void Draw(double scale = 1.0);
	virtual void Clean();
	virtual void reset();
	virtual inline void setGravity(double G) { Enemy_RigidBody->setRigidBody_Gravity(G); } 
	virtual inline Collider* getCollider() { return Enemy_Collider; }
	virtual inline bool isAttacking() { return false; }
	virtual inline double getAttacktime() { return 0; }
	virtual inline int getAttackPower() { return 0; }
	virtual void AnimationState() = 0;
	virtual void move(Uint64 dt) = 0;
	virtual inline void setAttackPower(int power) { Enemy_AttackPower = power; }

	void getPlayerPosition();
};

class Zombie : public Enemy{
public:
	Zombie(Properties* props) : Enemy(props) {};
	virtual void AnimationState();
	virtual void move(Uint64 dt);
};

class Skeleton : public Enemy{
public:
	Skeleton(Properties* props) : Enemy(props) {};
	virtual void AnimationState();
	virtual void move(Uint64 dt);
};