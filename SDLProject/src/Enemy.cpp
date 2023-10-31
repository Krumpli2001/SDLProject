#include "Enemy.hpp"

//hule vagyok, rust tett ilyenne de nem baj - elobb-utobb ugy is kell majd nekik kulon class
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

	getPlayerPosition();
	move(dt);

	//x axis collision
	Enemy_LastSafePosition.setX(GameObject_Transform->getX());
	GameObject_Transform->setX(GameObject_Transform->getX() + Enemy_RigidBody->getRigidBody_Position().getX());
	Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 190, 240);

	if (CollisionHandler::GetInstance()->MapCollision(this))
	{
		GameObject_Transform->setX(Enemy_LastSafePosition.getX());
		fal = true;
	}
	else { fal = false; }

	//y axis collision
	Enemy_LastSafePosition.setY(GameObject_Transform->getY());
	//levitalas miatt van itt
	int y = Enemy_LastSafePosition.getY();
	if ((y % CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize()) >= (CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize() - 10)) {
		Enemy_LastSafePosition.setY(GameObject_Transform->getY() + ((CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize() - 1)) - (y % CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize()));
	}

	GameObject_Transform->setY(GameObject_Transform->getY() + Enemy_RigidBody->getRigidBody_Position().getY());
	Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 190, 240);

	if (CollisionHandler::GetInstance()->MapCollision(this))
	{
		if (y > CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize()) {
			Enemy_IsGrounded = true;
		}
		GameObject_Transform->setY(Enemy_LastSafePosition.getY());
	}
	else
	{
		Enemy_IsGrounded = false;
	}

	//Enemy_SpriteAnimation->SetProps("zombie_idle", 0, 4, 400);
	AnimationState();
	Enemy_RigidBody->Update(dt);
	Enemy_SpriteAnimation->Update(dt);

}

void Enemy::Draw(double scale)
{
	Enemy_SpriteAnimation->Draw(GameObject_Transform->getX(), GameObject_Transform->getY(), GameObject_Width, GameObject_Height, GameObject_Flip, scale);
}

void Enemy::Clean()
{
	TextureManager::GetInstance()->Drop(GameObject_TextureID);
}

void Enemy::reset()
{
	hp = 0;
}

void Enemy::getPlayerPosition()
{
	Enemy_TargetPosX = Engine::GetInstance()->getGameObjects()[0]->getPosition()->getX();
	Enemy_TargetPosY = Engine::GetInstance()->getGameObjects()[0]->getPosition()->getY();
}
