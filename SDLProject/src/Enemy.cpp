#include "Enemy.hpp"

Enemy::Enemy(Properties* props) : Character(props)
{
	Enemy_RigidBody = new RigidBody();
	Enemy_RigidBody->setRigidBody_Gravity(3.0);
	Enemy_Collider = new Collider();

}

void Enemy::Update(Uint64 dt)
{
	//Enemy_RigidBody->Update(dt);

	Enemy_LastSafePosition.setX(GameObject_Transform->getX());
	GameObject_Transform->setX(GameObject_Transform->getX() + Enemy_RigidBody->getRigidBody_Position().getX());
	Enemy_Collider->setBox(GameObject_Transform->getX(), GameObject_Transform->getY(), 120, 120);

	if (CollisionHandler::GetInstance()->MapCollision(Enemy_Collider->getBox()))
	{
		GameObject_Transform->setX(Enemy_LastSafePosition.getX());
	}

	Enemy_LastSafePosition.setY(GameObject_Transform->getY());
	GameObject_Transform->setY(GameObject_Transform->getY() + Enemy_RigidBody->getRigidBody_Position().getY());
	Enemy_Collider->setBox(GameObject_Transform->getX(), GameObject_Transform->getY(), 120, 120);

	if (CollisionHandler::GetInstance()->MapCollision(Enemy_Collider->getBox()))
	{
		GameObject_Transform->setY(Enemy_LastSafePosition.getY());
	}



}

void Enemy::Draw()
{
}

void Enemy::Clean()
{
}
