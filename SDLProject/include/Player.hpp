#pragma once

#include "Character.hpp"
#include "SpriteAnimation.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "CollisionHandler.hpp"
#include "Timer.hpp"

#define JUMP_TIME 15.0
#define JUMP_FORCE 30.0
#define RUN_FORCE 5.0
#define ATTACK_TIME 40.0

class Player : public Character {
private:

	bool Player_IsWalking;
	bool Player_IsJumping;
	bool Player_IsFalling;
	bool Player_IsGrounded;
	bool Player_IsAttacking;
	bool Player_IsWalkAttacking;

	double Player_JumpTime;
	double Player_JumpForce;
	double Player_AttackTime;

	double Player_DeltaTime;

	Collider* Player_Collider;
	SpriteAnimation* Player_SpriteAnimation;
	RigidBody* Player_RigidBody;
	Vector2D Player_LastSafePosition;

	void AnimationState();
public:

	Player(Properties* props);

	virtual void Draw();
	virtual void Update(double dt);
	virtual void Clean();
};