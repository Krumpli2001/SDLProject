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
#define ATTACK_TIME 300.0

class Player : public Character {
private:

	bool Player_IsWalking;
	bool Player_IsJumping;
	bool Player_IsFalling;
	bool Player_IsGrounded;
	bool Player_IsAttacking;
	bool Player_IsWalkAttacking;

	Uint64 Player_JumpTime;
	double Player_AttackTime;

	Collider* Player_Collider;
	SpriteAnimation* Player_SpriteAnimation;
	RigidBody* Player_RigidBody;
	Vector2D Player_LastSafePosition;

	void AnimationState();
public:

	Player(Properties* props);

	inline RigidBody* getPlayerBody() { return Player_RigidBody; }

	virtual void Draw();
	virtual void Update(Uint64 dt);
	virtual void Clean();
	inline void setGravity(double G) { Player_RigidBody->setRigidBody_Gravity(G); }
};