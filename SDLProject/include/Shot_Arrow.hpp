#pragma once

#include "Engine.hpp"
#include "ObjectFactory.hpp"


class Shot_Arrow : public GameObject {
private:
	RigidBody* Arrow_RigidBody;
	Collider* Arrow_Collider;
	Vector2D Arrow_LastSafePosition;
	SpriteAnimation* Arrow_SpriteAnimation;

	int OriginalX = -1;
	int OriginalY = -1;

	int TargetPosX{};
	int TargetPosY{};

	double angle = 0;
	//bal=-1 jobb=1
	int irany = 0;

	int attackPower = 10;

public:
	inline Shot_Arrow(Properties* props) : GameObject(props) {
		GameObject_hp = props->Properies_hp;
		Arrow_RigidBody = new RigidBody();
		Arrow_RigidBody->setRigidBody_Gravity(GRAVITY);
		Arrow_Collider = new Collider();
		Arrow_SpriteAnimation = new SpriteAnimation();
		TargetPosX = (*Engine::GetInstance()->getGameObjects())[0]->getPosition()->getX() + (*Engine::GetInstance()->getGameObjects())[0]->getCollider()->getBox()->w / 2;
		TargetPosY = (*Engine::GetInstance()->getGameObjects())[0]->getPosition()->getY() + (*Engine::GetInstance()->getGameObjects())[0]->getCollider()->getBox()->h / 2;;
		Arrow_SpriteAnimation->SetProps("shot_arrow", 0, 1, 1);
	}

	//támadás
	virtual void attacking(Uint64 dt);

	//
	virtual void setAttacking(bool e) {}

	//
	virtual bool getAttacking() { return true; }

	//visszaadja a collidert
	virtual Collider* getCollider() { return Arrow_Collider; }

	// frissítés
	void Update(Uint64 dt);

	//kiírás
	void Draw();

	//törlás/felszabadítás
	void Clean();

	//reset
	void reset();

	//beállítja a gravitációt
	virtual void setGravity(double G) {}

	//
	virtual double getAttacktime() { return 0; }

	//visszaadja a nyíl sebzését
	int getAttackPower() { return attackPower; }

	//beáállítja a sebzést
	virtual void setAttackPower(int power) { power = attackPower; }

	//
	inline void* getInventory() override { return nullptr; }

	//
	inline int getSelectedInventory() { return 0; }

	//
	virtual void saveInventory() { return; }

	//
	virtual void readInventory() { return; }

	//beállítja a célpontot
	void setTarget(int X, int Y) { TargetPosX = X; TargetPosY = Y; }

};