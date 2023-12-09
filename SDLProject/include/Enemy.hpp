#pragma once

#include "Character.hpp"
//#include "RigidBody.hpp"
//#include "SpriteAnimation.hpp"
#include "ObjectFactory.hpp"
#include "Engine.hpp"

class Enemy : public Character
{
protected:
	Collider* Enemy_Collider;
	RigidBody* Enemy_RigidBody;
	Vector2D Enemy_LastSafePosition;

	SpriteAnimation* Enemy_SpriteAnimation;

	bool Enemy_IsAttacking = true;
	int Enemy_AttackPower{};
	double Enemy_AttackTimer = {};

	int Enemy_TargetPosX{};
	int Enemy_TargetPosY{};

	bool fal = false;

	bool Enemy_IsGrounded = false;
	bool Enemy_IsJumping = false;
	bool Enemy_IsFalling = false;
	double Enemy_JumpTime{};

public:
	Enemy(Properties* props);

	virtual void Update(Uint64 dt);
	virtual void Draw(double scale = 1.0);
	virtual void Clean();
	virtual void reset();
	virtual bool attacking(Uint64 dt) = 0;
	virtual inline void setGravity(double G) { Enemy_RigidBody->setRigidBody_Gravity(G); } 
	virtual inline Collider* getCollider() { return Enemy_Collider; }
	virtual inline bool isAttacking() { return Enemy_IsAttacking; }
	virtual inline void setAttacking(bool e) { Enemy_IsAttacking = e; }
	virtual inline double getAttacktime() { return Enemy_AttackTimer; }
	virtual inline int getAttackPower() { return 0; }
	virtual void AnimationState() = 0;
	virtual void move(Uint64 dt) = 0;
	virtual inline void setAttackPower(int power) { Enemy_AttackPower = power; }

	virtual inline void Enemy_Collision(Uint64 dt);

	void getPlayerPosition();
};

class Zombie : public Enemy{
private:
	
	
public:
	inline Zombie(Properties* props) : Enemy(props) {
		Enemy_AttackPower = 10;
		Enemy_AttackTimer = 1000;
	};
	virtual void AnimationState();
	virtual void move(Uint64 dt);
	virtual bool attacking(Uint64 dt);
	inline int getAttackPower() { return Enemy_AttackPower; }
	inline double getAttackTimer() { return Enemy_AttackTimer; }
};

class Skeleton : public Enemy{
private:
	
public:
	Skeleton(Properties* props) : Enemy(props) {
		Enemy_AttackTimer = 3000;
	};
	virtual void AnimationState();
	virtual void move(Uint64 dt);
	virtual bool attacking(Uint64 dt);
};
