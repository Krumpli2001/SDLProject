#include "Shot_Arrow.hpp"
#include <cmath>

static Registrar < Shot_Arrow > registrararrow("ARROW");

void Shot_Arrow::attacking(Uint64 dt)
{
	auto player = (*Engine::GetInstance()->getGameObjects()).front();
	if (CollisionHandler::GetInstance()->CheckCollision(*this->Arrow_Collider->getBox(), *player->getCollider()->getBox())) {
		GameObject_hp = 0;
		player->setHP(player->getHP() - getAttackPower());
		player->TookDMG(irany);
	}
}

void Shot_Arrow::Update(Uint64 dt)
{
	Arrow_RigidBody->SetForceToZero();

	/*if (irany == 0) {
		if (TargetPosX < GameObject_Transform->getX()) {
			irany = -1;
		}
		else {
			irany = 1;
		}
		irany = TargetPosX < GameObject_Transform->getX() ? -1 : 1;
	}*/

	//ez aztan a c, a felso resz a magyarazat XD
	irany = irany == 0 ? irany = TargetPosX < GameObject_Transform->getX() ? BALRA : JOBBRA : irany;

	if (OriginalX == -1 and OriginalY == -1) {
		OriginalX = static_cast<int>(GameObject_Transform->getX());
		OriginalY = static_cast<int>(GameObject_Transform->getY());
	}

	double distX = abs(OriginalX - TargetPosX);
	//double distY = abs(OriginalY - TargetPosY);

	//double distPerKetto = distX / 2;

	double ForceY = maxY - ((abs(GameObject_Transform->getX() - OriginalX)) / (distX / 2.0));

	if (irany==BALRA) {
		Arrow_RigidBody->ApplyForceX(BALRA * 2);
		Arrow_RigidBody->ApplyForceY(FEL * ForceY);
	}
	else {
		Arrow_RigidBody->ApplyForceX(JOBBRA * 2);
		Arrow_RigidBody->ApplyForceY(FEL * ForceY);
	}

	constexpr auto radian /*ha jol emlekszem*/ = 180;
	if (irany==BALRA) {
		angle = 90  - atan(Arrow_RigidBody->getRigidBody_Velocity().getY() / Arrow_RigidBody->getRigidBody_Velocity().getX()) * (-radian) / M_PI;
	}
	else {
		angle = 270 - atan(Arrow_RigidBody->getRigidBody_Velocity().getY() / Arrow_RigidBody->getRigidBody_Velocity().getX()) * (-radian) / M_PI;
	}

	GameObject_Transform->setX(GameObject_Transform->getX() + Arrow_RigidBody->getRigidBody_Position().getX());
	GameObject_Transform->setY(GameObject_Transform->getY() + Arrow_RigidBody->getRigidBody_Position().getY());
	//w és h 1, hogy ne akadjanak fent dolgokban
	Arrow_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 1, 1);

	if (CollisionHandler::GetInstance()->MapCollision(this)) {
		GameObject_hp = 0;
	}

	GameObject_Origin->setX(GameObject_Transform->getX());
	GameObject_Origin->setY(GameObject_Transform->getY());

	Arrow_RigidBody->Update(dt);
}

void Shot_Arrow::Draw()
{
	Arrow_SpriteAnimation->Draw(GameObject_Transform->getX(), GameObject_Transform->getY(), GameObject_Width, GameObject_Height, SDL_FLIP_VERTICAL, angle);
}

void Shot_Arrow::Clean()
{
	TextureManager::GetInstance()->Drop(GameObject_TextureID);
}

void Shot_Arrow::reset()
{
	GameObject_hp = 0;
}