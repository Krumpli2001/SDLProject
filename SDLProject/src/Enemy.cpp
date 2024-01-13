#include "Enemy.hpp"

//hule vagyok, rust tett ilyenne de nem baj - elobb-utobb ugy is kell majd nekik kulon class
//static Registrar < Zombie > registrar("ZOMBIE");
//static Registrar < Skeleton > registrar("SKELETON");

Enemy::Enemy(Properties* props) : Character(props)
{
	GameObject_hp = props->Properies_hp;
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
	Enemy_Collision(dt);
	//attacking(dt);
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
	GameObject_hp = 0;
}

void Enemy::getPlayerPosition()
{
	Enemy_TargetPosX = (*Engine::GetInstance()->getGameObjects())[0]->getPosition()->getX();
	Enemy_TargetPosY = (*Engine::GetInstance()->getGameObjects())[0]->getPosition()->getY();
}

void Enemy::Enemy_Collision(Uint64 dt) {

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
			//std::cout << "e " << szam << "\n";
			szam += 1;
			Enemy_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()) + dt * Enemy_RigidBody->getGravity() - szam, 190, 240);
			if (szam > CollisionHandler::GetInstance()->getTileSize()) { break; }
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