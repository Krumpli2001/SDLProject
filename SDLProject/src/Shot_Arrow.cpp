#include "Shot_Arrow.hpp"
#include <cmath>

static Registrar < Shot_Arrow > registrararrow("ARROW");

void Shot_Arrow::attacking(Uint64 dt)
{
	auto player = (*Engine::GetInstance()->getGameObjects())[0];
	if (CollisionHandler::GetInstance()->CheckCollision(*this->Arrow_Collider->getBox(), *player->getCollider()->getBox())) {
		GameObject_hp = 0;
		player->setHP(player->getHP() - getAttackPower());
		player->TookDMG(FEL * 100, 550);
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
	irany = irany == 0 ? irany = TargetPosX < GameObject_Transform->getX() ? -1 : 1:irany;

	if (OriginalX == -1 and OriginalY == -1) {
		OriginalX = GameObject_Transform->getX();
		OriginalY = GameObject_Transform->getY();
	}

	int distX = abs(OriginalX - TargetPosX);
	int distY = abs(OriginalY - TargetPosY);

	double maxY = 2;
	int distPerKetto = distX / 2;

	double ForceY = maxY - ((abs(GameObject_Transform->getX() - OriginalX)) / distPerKetto);

	if (irany==-1) {
		Arrow_RigidBody->ApplyForceX(BALRA * 2);
		if (OriginalX - GameObject_Transform->getX() < distX / 2) {
			Arrow_RigidBody->ApplyForceY(FEL * ForceY);
		}
	}
	else {
		Arrow_RigidBody->ApplyForceX(JOBBRA * 2);
		if (OriginalX - GameObject_Transform->getX() < distX / 2) {
			Arrow_RigidBody->ApplyForceY(FEL * ForceY);
		}
	}

	if (Arrow_RigidBody->getRigidBody_Velocity().getX() < 0) {
		angle = 90 - atan(Arrow_RigidBody->getRigidBody_Velocity().getY() / Arrow_RigidBody->getRigidBody_Velocity().getX()) * (-180) / M_PI;
	}
	else {
		angle = 270 - atan(Arrow_RigidBody->getRigidBody_Velocity().getY() / Arrow_RigidBody->getRigidBody_Velocity().getX()) * (-180) / M_PI;
	}


	if (CollisionHandler::GetInstance()->MapCollision(this)) {
		GameObject_hp = 0;
	}

	GameObject_Transform->setX(GameObject_Transform->getX() + Arrow_RigidBody->getRigidBody_Position().getX());
	GameObject_Transform->setY(GameObject_Transform->getY() + Arrow_RigidBody->getRigidBody_Position().getY());
	Arrow_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 20, 100);

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