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

void Skeleton::Enemy_Collision(Uint64 dt)
{
	//x axis collision
	Enemy_LastSafePosition.setX(GameObject_Transform->getX());
	GameObject_Transform->setX(GameObject_Transform->getX() + Enemy_RigidBody->getRigidBody_Position().getX());
	Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 190, 240);

	if (CollisionHandler::GetInstance()->MapCollision(this, &Enemy_IsGrounded))
	{
		GameObject_Transform->setX(Enemy_LastSafePosition.getX());
		fal = true;
	}
	else { fal = false; }

	//y axis collision
	Enemy_LastSafePosition.setY(GameObject_Transform->getY());
	//levitalas miatt van itt

	if ((static_cast<int>(Enemy_LastSafePosition.getY()) % CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize()) >= (CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize() - dt * Enemy_RigidBody->getGravity())) {

		int szam = 0;
		Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()) + dt * Enemy_RigidBody->getGravity() - szam, 190, 240);
		while (CollisionHandler::GetInstance()->MapCollision(this, &Enemy_IsGrounded)) {
			szam += 1;
			Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()) + dt * Enemy_RigidBody->getGravity() - szam, 190, 240);
		}
		Enemy_LastSafePosition.setY(GameObject_Transform->getY() + dt * Enemy_RigidBody->getGravity() - szam);

		//Enemy_LastSafePosition.setY(GameObject_Transform->getY() + ((CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize() - 1)) - (static_cast<int>(Enemy_LastSafePosition.getY()) % CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize()));
	}

	GameObject_Transform->setY(GameObject_Transform->getY() + Enemy_RigidBody->getRigidBody_Position().getY());
	Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 190, 240);

	if (CollisionHandler::GetInstance()->MapCollision(this, &Enemy_IsGrounded))
	{
		if (Enemy_IsGrounded) {
			Enemy_JumpTime = 200;
		}
		GameObject_Transform->setY(Enemy_LastSafePosition.getY());
	}
	else
	{
		Enemy_IsGrounded = false;
	}
}

bool Skeleton::attacking(Uint64 dt)
{
	return false;
}
