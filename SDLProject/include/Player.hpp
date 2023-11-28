#pragma once

#include "Character.hpp"
#include "SpriteAnimation.hpp"
#include "RigidBody.hpp"
#include "Timer.hpp"

//az ido ms
#define JUMP_TIME 200.0
#define JUMP_FORCE 3.0
#define RUN_FORCE 1.0
#define UNDER_WATER_TIME 10000

class Player : public Character {
private:

	bool Player_IsWalking;
	bool Player_IsJumping;
	bool Player_IsFalling;
	bool Player_IsGrounded;
	bool Player_IsAttacking;
	bool Player_IsWalkAttacking;

	double Player_JumpForce;

	bool Player_IsUnderWater;
	double Player_UnderWater;

	double Player_JumpTime;
	double Player_AttackTime;
	int Player_AttackPower = 15;

	Collider* Player_Collider;
	SpriteAnimation* Player_SpriteAnimation;
	RigidBody* Player_RigidBody;
	Vector2D Player_LastSafePosition;

	void AnimationState();
public:

	Player(Properties* props);

	inline RigidBody* getPlayerBody() { return Player_RigidBody; }
	inline void setUnderWater(bool e) { Player_IsUnderWater = e; }
	virtual inline Collider* getCollider() { return Player_Collider; }

	virtual void Draw(double scale = 1.0);
	virtual void Update(Uint64 dt);
	virtual void Clean();
	virtual void reset();
	virtual inline void setGravity(double G) { Player_RigidBody->setRigidBody_Gravity(G); }

	virtual inline double getAttacktime() { return Player_AttackTime; }
	virtual inline int getAttackPower() { return Player_AttackPower; }
	virtual inline void setAttackPower(int power) { Player_AttackPower = power; }

	virtual inline bool isAttacking() { return Player_IsAttacking; }
	inline double getPGravity() { return Player_RigidBody->getGravity(); }
	//inline Transform* getPlayerPosition() { return GameObject_Transform; }
};