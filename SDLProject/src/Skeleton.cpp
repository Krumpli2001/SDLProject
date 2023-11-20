#include "Enemy.hpp"

static Registrar < Skeleton > registrar("SKELETON");

void Skeleton::AnimationState() {
	Enemy_SpriteAnimation->SetProps("skeleton_idle", 0, 4, 400);
}

void Skeleton::move(Uint64 dt)
{
	//fut jobbra
	if (Enemy_TargetPosX - 100 > GameObject_Transform->getX())
	{
		Enemy_RigidBody->ApplyForceX(JOBBRA * 0.1);
		GameObject_Flip = SDL_FLIP_NONE;
	}

	//fut balra
	if (Enemy_TargetPosX + 100 < GameObject_Transform->getX())
	{
		Enemy_RigidBody->ApplyForceX(BALRA * 0.1);
		GameObject_Flip = SDL_FLIP_HORIZONTAL;
	}

	//jump
	if (fal and Enemy_JumpTime > 0 and Enemy_JumpTime <= 200) {
		Enemy_RigidBody->ApplyForceY(FEL * 1.7);
		Enemy_JumpTime -= dt;
	}
	if (Enemy_IsGrounded)
	{
		Enemy_JumpTime = 200.0;
	}

}