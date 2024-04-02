#include "Enemy.hpp"
#include "ObjectFactory.hpp"

static Registrar < Skeleton > registrar("SKELETON");

void Skeleton::AnimationState() {
	Enemy_SpriteAnimation->SetProps("skeleton_idle", 0, 4, 400);
}

void Skeleton::move(Uint64 dt)
{

	if (!isAiming) {
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

}

void Skeleton::attacking(Uint64 dt)
{
	constexpr auto attack_tavolsag = 10;
	constexpr auto skeleton_attackTimer = 3000;
	if (abs(Enemy_TargetPosX - GameObject_Transform->getX()) < attack_tavolsag * Engine::GetInstance()->getTileSize()) {
		isAiming = true;
		if (Enemy_AttackTimer == skeleton_attackTimer) {
			Enemy_AttackTimer -= dt;
			Engine::GetInstance()->spawnSpecial("ARROW", GameObject_Transform->getX() + GameObject_Dimenziok.w / 2, GameObject_Transform->getY() + GameObject_Dimenziok.h / 2, 1, 10);
		}
	}
	else {
		isAiming = false;
	}
	Enemy_AttackTimer = Enemy_AttackTimer < 0 ? skeleton_attackTimer : Enemy_AttackTimer;
	Enemy_AttackTimer = Enemy_AttackTimer != skeleton_attackTimer ? Enemy_AttackTimer -= dt : Enemy_AttackTimer;
}
