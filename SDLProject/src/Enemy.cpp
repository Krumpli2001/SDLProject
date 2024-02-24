#include "Enemy.hpp"

Enemy::Enemy(Properties* props) : Character(props)
{
	GameObject_hp = props->Properies_hp;
	Enemy_RigidBody = new RigidBody();
	Enemy_RigidBody->setRigidBody_Gravity(GRAVITY);
	Enemy_Collider = new Collider();

	Enemy_SpriteAnimation = new SpriteAnimation();

}

void Enemy::Update(Uint64 dt)
{

	Enemy_RigidBody->SetForceToZero();
	getPlayerPosition();
	move(dt);
	Enemy_Collision(dt);
	AnimationState();
	Enemy_RigidBody->Update(dt);
	Enemy_SpriteAnimation->Update(dt);

}

void Enemy::Draw()
{
	Enemy_SpriteAnimation->Draw(GameObject_Transform->getX(), GameObject_Transform->getY(), GameObject_Width, GameObject_Height, GameObject_Flip, 0.0, 1.0, Enemy_dimenziok.w, Enemy_dimenziok.h);
}

void Enemy::Clean()
{
	TextureManager::GetInstance()->Drop(GameObject_TextureID);
}

void Enemy::reset()
{
	GameObject_hp = 0;
}

void Enemy::getPlayerPosition()
{
	Enemy_TargetPosX = static_cast<int>((*Engine::GetInstance()->getGameObjects())[0]->getPosition()->getX());
	Enemy_TargetPosY = static_cast<int>((*Engine::GetInstance()->getGameObjects())[0]->getPosition()->getY());
}

void Enemy::Enemy_Collision(Uint64 dt) {

	//x axis collision
	Enemy_LastSafePosition.setX(GameObject_Transform->getX());
	GameObject_Transform->setX(GameObject_Transform->getX() + Enemy_RigidBody->getRigidBody_Position().getX());
	Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), Enemy_dimenziok.w, Enemy_dimenziok.h);

	if (CollisionHandler::GetInstance()->MapCollision(this, &Enemy_IsGrounded))
	{
		GameObject_Transform->setX(Enemy_LastSafePosition.getX());
		fal = true;
	}
	else {
		fal = false;
	}

	//y axis collision
	Enemy_LastSafePosition.setY(GameObject_Transform->getY());
	//levitalas miatt van itt

	if ((static_cast<int>(Enemy_LastSafePosition.getY()) % CollisionHandler::GetInstance()->getCollisionLayer()->getTileSize()) >= (CollisionHandler::GetInstance()->getCollisionLayer()->getTileSize() - dt * Enemy_RigidBody->getGravity())) {
	
		auto szam = ((static_cast<int>(Enemy_LastSafePosition.getY()) + GameObject_Height) % CollisionHandler::GetInstance()->getCollisionLayer()->getTileSize());
		Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()) + dt * Enemy_RigidBody->getGravity() - szam, Enemy_dimenziok.w, Enemy_dimenziok.h);
		if (CollisionHandler::GetInstance()->MapCollision(this, &Enemy_IsGrounded))
		{
			GameObject_Transform->setX(Enemy_LastSafePosition.getX());
		}
		Enemy_LastSafePosition.setY(GameObject_Transform->getY());

	}

	GameObject_Transform->setY(GameObject_Transform->getY() + Enemy_RigidBody->getRigidBody_Position().getY());
	Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), Enemy_dimenziok.w, Enemy_dimenziok.h);

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