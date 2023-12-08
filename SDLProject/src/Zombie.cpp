#include "Enemy.hpp"

static Registrar < Zombie > registrar("ZOMBIE");

void Zombie::AnimationState() {
	Enemy_SpriteAnimation->SetProps("zombie_idle", 0, 4, 400);
 }

void Zombie::move(Uint64 dt)
{
	//fut jobbra
	if (Enemy_TargetPosX - 100 > GameObject_Transform->getX())
	{
		Enemy_RigidBody->ApplyForceX(JOBBRA * 0.3);
		GameObject_Flip = SDL_FLIP_NONE;
	}

	//fut balra
	if (Enemy_TargetPosX + 100 < GameObject_Transform->getX())
	{
		Enemy_RigidBody->ApplyForceX(BALRA * 0.3);
		GameObject_Flip = SDL_FLIP_HORIZONTAL;
	}

	//jump
	if (fal and Enemy_IsGrounded) {
		Enemy_RigidBody->ApplyForceY(FEL * 2.5);
		//Enemy_JumpTime -= dt;
		Enemy_IsGrounded = false;
		Enemy_IsJumping = true;
	}
	if(Enemy_IsJumping and Enemy_JumpTime > 0) { 
		Enemy_JumpTime -= dt;
		Enemy_RigidBody->ApplyForceY(FEL * 2.5);
	}
	else { Enemy_IsJumping = false; }

	//zuhan
	if (Enemy_RigidBody->getRigidBody_Velocity().getY() > 0 and !Enemy_IsGrounded)
	{
		Enemy_IsFalling = true;
	}
	else
	{
		Enemy_IsFalling = false;
	}

}

bool Zombie::attacking(Uint64 dt)
{
	if (Enemy_IsAttacking)
	{
		Enemy_AttackTimer -= dt;
		Enemy_IsAttacking = false;
		return true;
	}

	if ( !Enemy_IsAttacking and Enemy_AttackTimer < 1000) {
		Enemy_AttackTimer -= dt;
	}

	if (Enemy_AttackTimer < 0) {
		Enemy_AttackTimer = 1000;
		Enemy_IsAttacking = true;
	}

	return false;
}
