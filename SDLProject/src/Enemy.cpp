#include "Enemy.hpp"

Enemy::Enemy(Properties* props) : Character(props)
{
	GameObject_hp = props->Properies_hp;
	Enemy_RigidBody = new RigidBody();
	Enemy_RigidBody->setRigidBody_Gravity(GRAVITY);
	Enemy_Collider = new Collider();

	Enemy_SpriteAnimation = new SpriteAnimation();

}

Enemy::~Enemy()
{
	delete Enemy_RigidBody;
	delete Enemy_Collider;
	delete Enemy_SpriteAnimation;
}

void Enemy::Update(Uint64 dt)
{
	Enemy_RigidBody->SetForceToZero();
	getPlayerPosition();
	move(dt);
	Enemy_Collision(dt);

	GameObject_Origin->setX(GameObject_Transform->getX()+GameObject_Width/2);
	GameObject_Origin->setY(GameObject_Transform->getY() + GameObject_Height / 2);

	AnimationState();
	Enemy_RigidBody->Update(dt);
	Enemy_SpriteAnimation->Update(dt);
}

void Enemy::Draw()
{
	Enemy_SpriteAnimation->Draw(GameObject_Transform->getX(), GameObject_Transform->getY(), GameObject_Width, GameObject_Height,
		GameObject_Flip, 0.0, 1.0, GameObject_Dimenziok.w, GameObject_Dimenziok.h);
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
	auto playerPos = (*Engine::GetInstance()->getGameObjects()).front()->getOrigin();
	Enemy_TargetPosX = static_cast<int>(playerPos->getX());
	Enemy_TargetPosY = static_cast<int>(playerPos->getY());
}

void Enemy::Enemy_Collision(Uint64 dt) {

	//x axis collision
	Enemy_LastSafePosition.setX(GameObject_Transform->getX());
	GameObject_Transform->setX(GameObject_Transform->getX() + Enemy_RigidBody->getRigidBody_Position().getX());
	Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()),
		GameObject_Dimenziok.w, GameObject_Dimenziok.h);

	auto collisionHandlerInstance = CollisionHandler::GetInstance();

	if (collisionHandlerInstance->MapCollision(this, &Enemy_IsGrounded))
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

	if ((static_cast<int>(Enemy_LastSafePosition.getY()) % collisionHandlerInstance->getCollisionLayer()->getTileSize()) >= (collisionHandlerInstance->getCollisionLayer()->getTileSize() - dt * Enemy_RigidBody->getGravity())) {
	
		auto szam = ((static_cast<int>(Enemy_LastSafePosition.getY()) + GameObject_Height) % collisionHandlerInstance->getCollisionLayer()->getTileSize());
		Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()),
			static_cast<int>(GameObject_Transform->getY() + dt * Enemy_RigidBody->getGravity() - szam), GameObject_Dimenziok.w, GameObject_Dimenziok.h);
		if (collisionHandlerInstance->MapCollision(this, &Enemy_IsGrounded))
		{
			GameObject_Transform->setX(Enemy_LastSafePosition.getX());
		}
		Enemy_LastSafePosition.setY(GameObject_Transform->getY());

	}

	GameObject_Transform->setY(GameObject_Transform->getY() + Enemy_RigidBody->getRigidBody_Position().getY());
	Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()),
		static_cast<int>(GameObject_Transform->getY()), GameObject_Dimenziok.w, GameObject_Dimenziok.h);

	if (collisionHandlerInstance->MapCollision(this, &Enemy_IsGrounded))
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