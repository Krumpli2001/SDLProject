#include "Enemy.hpp"
#include "ObjectFactory.hpp"

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
	if (fal and Enemy_IsGrounded) {
		Enemy_RigidBody->ApplyForceY(FEL * 1.7);
		//Enemy_JumpTime -= dt;
		Enemy_IsGrounded = false;
		Enemy_IsJumping = true;
	}
	if (Enemy_IsJumping and Enemy_JumpTime > 0) {
		Enemy_JumpTime -= dt;
		Enemy_RigidBody->ApplyForceY(FEL * 1.7);
	}
	else { Enemy_IsJumping = false; }

	//zuhanas
	if (Enemy_RigidBody->getRigidBody_Velocity().getY() > 0 and !Enemy_IsGrounded)
	{
		Enemy_IsFalling = true;
	}
	else
	{
		Enemy_IsFalling = false;
	}

}

bool Skeleton::attacking(Uint64 dt)
{
	Engine::GetInstance()->spawnSpecial("ARROW", Enemy_RigidBody->getRigidBody_Position().getX(), Enemy_RigidBody->getRigidBody_Position().getY(), 1, 10);
	//Engine::GetInstance()->getGameObjects()->push_back(ObjectFactory::GetInstance()->CreateObject("ARROW", Engine::GetInstance()->getPropsMap()->find("ARROW")->second));
	return false;
}
