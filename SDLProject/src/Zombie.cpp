#include "Enemy.hpp"

static Registrar < Zombie > registrar("ZOMBIE");

void Zombie::AnimationState() {
	Enemy_SpriteAnimation->SetProps("zombie_idle", 0, 4, 400);
 }

void Zombie::move(Uint64 dt)
{
	//fut jobbra
	if (Enemy_TargetPosX-100 > GameObject_Transform->getX())
	{
		Enemy_RigidBody->ApplyForceX(JOBBRA * 0.3);
		GameObject_Flip = SDL_FLIP_NONE;
	}

	//fut balra
	if (Enemy_TargetPosX+100 < GameObject_Transform->getX())
	{
		Enemy_RigidBody->ApplyForceX(BALRA * 0.3);
		GameObject_Flip = SDL_FLIP_HORIZONTAL;
	}

	//jump
	if (fal and Enemy_JumpTime > 0 and Enemy_IsGrounded) {
		Enemy_RigidBody->ApplyForceY(FEL * 2.5);
		Enemy_JumpTime -= dt;
	}
	if(Enemy_IsGrounded)
	{ Enemy_JumpTime = 200.0; }

}