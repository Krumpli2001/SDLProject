#pragma once

#include "Character.hpp"
#include "SpriteAnimation.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "CollisionHandler.hpp"
#include "Timer.hpp"

//az ido ms
#define JUMP_TIME 200.0
#define JUMP_FORCE 3.0
#define RUN_FORCE 1.0
#define UNDER_WATER_TIME 10000.0

class Player : public Character {
private:

	//int Player_hp;

	bool Player_IsWalking;
	bool Player_IsJumping;
	bool Player_IsFalling;
	bool Player_IsGrounded;
	bool Player_IsAttacking;
	bool Player_IsWalkAttacking;

	bool Player_IsUnderWater;
	double Player_UnderWater;

	Uint64 Player_JumpTime;
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
	inline void setUnderWater(bool w) { Player_IsUnderWater = w; }
	virtual inline Collider* getCollider() { return Player_Collider; }

	virtual void Draw();
	virtual void Update(Uint64 dt);
	virtual void Clean();
	virtual void reset();
	virtual inline void setGravity(double G) { Player_RigidBody->setRigidBody_Gravity(G); }

	virtual inline double getAttacktime() { return Player_AttackTime; }
	virtual inline int getAttackPower() { return Player_AttackPower; }

	virtual inline bool isAttacking() { return Player_IsAttacking; }
	inline double getPGravity() { return Player_RigidBody->getGravity(); }
	//inline Transform* getPlayerPosition() { return GameObject_Transform; }
};