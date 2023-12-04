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
	GameObject_hp = 0;
}

void Enemy::getPlayerPosition()
{
	Enemy_TargetPosX = (*Engine::GetInstance()->getGameObjects())[0]->getPosition()->getX();
	Enemy_TargetPosY = (*Engine::GetInstance()->getGameObjects())[0]->getPosition()->getY();
}
