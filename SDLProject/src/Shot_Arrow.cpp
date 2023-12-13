#include "Shot_Arrow.hpp"
#include <cmath>

static Registrar < Shot_Arrow > registrararrow("ARROW");

bool Shot_Arrow::attacking(Uint64 dt)
{
	/*if (Enemy_AttackTimer == 1000) {
		Enemy_AttackTimer -= dt;*/
		GameObject_hp = 0;
		return true;
	//}
	//return false;
}

void Shot_Arrow::Update(Uint64 dt)
{
	//ehelyett a magic number kep meret helyett kell majd jobb megoldás...
	//Arrow_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 20, 100);
	Arrow_RigidBody->SetForceToZero();

	if (TargetPosX < GameObject_Transform->getX()) {
		Arrow_RigidBody->ApplyForceX(BALRA * 4);
	}
	else {
		Arrow_RigidBody->ApplyForceX(JOBBRA * 4);
	}


	bool kuka;
	if (CollisionHandler::GetInstance()->MapCollision(this, &kuka)) {
		GameObject_hp = 0;
	}

	GameObject_Transform->setX(GameObject_Transform->getX() + Arrow_RigidBody->getRigidBody_Position().getX());
	GameObject_Transform->setY(GameObject_Transform->getY() + Arrow_RigidBody->getRigidBody_Position().getY());
	Arrow_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 20, 100);

	//std::cout << Arrow_RigidBody->getRigidBody_Velocity().getY() << " " << Arrow_RigidBody->getRigidBody_Velocity().getX() << "\n";
	if(Arrow_RigidBody->getRigidBody_Velocity().getX() < 0)
		angle = 90 - atan(Arrow_RigidBody->getRigidBody_Velocity().getY() / Arrow_RigidBody->getRigidBody_Velocity().getX()) * ( - 180) / M_PI;

	else
		angle = 270 - atan(Arrow_RigidBody->getRigidBody_Velocity().getY() / Arrow_RigidBody->getRigidBody_Velocity().getX()) * (-180) / M_PI;

	//std::cout << angle << "\n";
	Arrow_RigidBody->Update(dt);
}

void Shot_Arrow::Draw(double scale)
{
	Arrow_SpriteAnimation->Draw(GameObject_Transform->getX(), GameObject_Transform->getY(), GameObject_Width, GameObject_Height, SDL_FLIP_VERTICAL, angle, scale);
}

void Shot_Arrow::Clean()
{
	TextureManager::GetInstance()->Drop(GameObject_TextureID);
}

void Shot_Arrow::reset()
{
	GameObject_hp = 0;
}