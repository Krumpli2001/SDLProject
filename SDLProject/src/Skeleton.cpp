#include "Enemy.hpp"
#include "ObjectFactory.hpp"

static Registrar < Skeleton > registrar("SKELETON");

void Skeleton::AnimationState() {
	Enemy_SpriteAnimation->SetProps("skeleton_idle", 0, 4, 400);
}

void Skeleton::move(Uint64 dt)
{
	if (Enemy_dimenziok.w == 0 and Enemy_dimenziok.h == 0) {
		Enemy_dimenziok = TextureManager::GetInstance()->getTextureMap()->find("skeleton_idle")->second.second;
	}

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
	if (abs(Enemy_TargetPosX - GameObject_Transform->getX()) < 10 * Engine::GetInstance()->getTileSize()) {
		isAiming = true;
		if (Enemy_AttackTimer == 3000) {
			Enemy_AttackTimer -= dt;
			Engine::GetInstance()->spawnSpecial("ARROW", GameObject_Transform->getX() + Enemy_dimenziok.w / 2, GameObject_Transform->getY() + Enemy_dimenziok.h / 2, 1, 10);
		}
	}
	else {
		isAiming = false;
	}
	Enemy_AttackTimer = Enemy_AttackTimer < 0 ? 3000 : Enemy_AttackTimer;
	Enemy_AttackTimer = Enemy_AttackTimer != 3000 ? Enemy_AttackTimer -= dt : Enemy_AttackTimer;
}
