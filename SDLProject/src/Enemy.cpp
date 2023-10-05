#include "Enemy.hpp"

//static Registrar < Zombie > registrar("ZOMBIE");
//static Registrar < Skeleton > registrar("SKELETON");

Enemy::Enemy(Properties* props) : Character(props)
{
	hp = props->Properies_hp;
	Enemy_RigidBody = new RigidBody();
	Enemy_RigidBody->setRigidBody_Gravity(GRAVITY);
	Enemy_Collider = new Collider();
	Enemy_Collider->setBuffer(0, 0, 0, 0);

	Enemy_SpriteAnimation = new SpriteAnimation();

}

void Enemy::Update(Uint64 dt)
{
	Enemy_RigidBody->SetForceToZero();

	Enemy_LastSafePosition.setX(GameObject_Transform->getX());
	GameObject_Transform->setX(GameObject_Transform->getX() + Enemy_RigidBody->getRigidBody_Position().getX());
	Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 190, 240);

	if (CollisionHandler::GetInstance()->MapCollision(Enemy_Collider->getBox()))
	{
		GameObject_Transform->setX(Enemy_LastSafePosition.getX());
	}

	Enemy_LastSafePosition.setY(GameObject_Transform->getY());
	//levitalas miatt van itt
	int y = Enemy_LastSafePosition.getY();
	if ((y % CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize()) >= (CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize() - 10)) {
		Enemy_LastSafePosition.setY(GameObject_Transform->getY() + ((CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize() - 1)) - (y % CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize()));
	}

	GameObject_Transform->setY(GameObject_Transform->getY() + Enemy_RigidBody->getRigidBody_Position().getY());
	Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 190, 240);

	if (CollisionHandler::GetInstance()->MapCollision(Enemy_Collider->getBox()))
	{
		GameObject_Transform->setY(Enemy_LastSafePosition.getY());
	}

	//Enemy_SpriteAnimation->SetProps("zombie_idle", 0, 4, 400);
	AnimationState();
	Enemy_RigidBody->Update(dt);
	Enemy_SpriteAnimation->Update(dt);

}

void Enemy::Draw()
{
	Enemy_SpriteAnimation->Draw(GameObject_Transform->getX(), GameObject_Transform->getY(), GameObject_Width, GameObject_Height, GameObject_Flip, 1.0, 1.0);
}

void Enemy::Clean()
{
	TextureManager::GetInstance()->Drop(GameObject_TextureID);
}