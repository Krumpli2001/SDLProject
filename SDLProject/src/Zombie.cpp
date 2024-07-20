#include "Enemy.hpp"

static Registrar < Zombie > registrar("ZOMBIE");

void Zombie::AnimationState() {
	auto texturemanagerInstance = TextureManager::GetInstance();

	Enemy_SpriteAnimation.SetProps("zombie_idle", 0, 4, 400);
	GameObject_Width = texturemanagerInstance->getTextureMap()->find("zombie_idle")->second.second.w;
	GameObject_Height = texturemanagerInstance->getTextureMap()->find("zombie_idle")->second.second.h;

	if (Character_AnimationState == IsWalking) {
		Enemy_SpriteAnimation.SetProps("zombie_walk", 0, 6, 400);
		GameObject_Width = texturemanagerInstance->getTextureMap()->find("zombie_walk")->second.second.w;
		GameObject_Height = texturemanagerInstance->getTextureMap()->find("zombie_walk")->second.second.h;
	}

	if (Enemy_AttackTimer < zombieAttacktimer) {
		Enemy_SpriteAnimation.SetProps("zombie_stand_hit", 0, 4, static_cast<int>(zombieAttacktimer / Enemy_SpriteAnimation.getFrameCount()), true);
		GameObject_Width = texturemanagerInstance->getTextureMap()->find("zombie_stand_hit")->second.second.w;
		GameObject_Height = texturemanagerInstance->getTextureMap()->find("zombie_stand_hit")->second.second.h;
	}
}

void Zombie::move(Uint64 dt)
{
	//fut jobbra
	if (Enemy_TargetPosX - 50 > GameObject_Origin.getX())
	{
		Enemy_RigidBody.ApplyForceX(JOBBRA * 0.3);
		GameObject_Flip = SDL_FLIP_NONE;
		Character_AnimationState = IsWalking;
	}

	//fut balra
	if (Enemy_TargetPosX + 50 < GameObject_Origin.getX())
	{
		Enemy_RigidBody.ApplyForceX(BALRA * 0.3);
		GameObject_Flip = SDL_FLIP_HORIZONTAL;
		Character_AnimationState = IsWalking;
	}

	//jump
	if (fal and Enemy_IsGrounded) {
		Enemy_RigidBody.ApplyForceY(FEL * 2.5);
		Enemy_IsGrounded = false;
		Enemy_IsJumping = true;
	}
	if(Enemy_IsJumping and Enemy_JumpTime > 0) { 
		Enemy_JumpTime -= dt;
		Enemy_RigidBody.ApplyForceY(FEL * 2.5);
	}
	else { Enemy_IsJumping = false; }

	//zuhan
	if (Enemy_RigidBody.getRigidBody_Velocity().getY() > 0 and !Enemy_IsGrounded)
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
	auto player = (*Engine::GetInstance()->getGameObjects())[0];
	if (CollisionHandler::GetInstance()->CheckCollision(*Enemy_Collider.getBox(), *player->getCollider()->getBox())) {
		if (Enemy_AttackTimer == zombieAttacktimer) {
			Enemy_AttackTimer -= dt;
			player->setHP(player->getHP() - Enemy_AttackPower);
			auto irany = player->getOrigin()->getX() < GameObject_Origin.getX() ? BALRA : JOBBRA;
			return true;
			//player->TookDMG(irany, 2, 50);
		}
	}

	Enemy_AttackTimer = Enemy_AttackTimer < 0 or Enemy_AttackTimer == zombieAttacktimer ? zombieAttacktimer : Enemy_AttackTimer -= dt;
	return false;
}
