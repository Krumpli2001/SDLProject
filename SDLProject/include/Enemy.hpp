#pragma once

#include "Character.hpp"
#include "Engine.hpp"
#include "ObjectFactory.hpp"

class Enemy : public Character
{
protected:
	Collider* Enemy_Collider;
	RigidBody* Enemy_RigidBody;
	Vector2D Enemy_LastSafePosition;

	SpriteAnimation* Enemy_SpriteAnimation;

	bool Enemy_IsAttacking = true;
	int Enemy_AttackPower{};
	double Enemy_AttackTimer = {};

	int Enemy_TargetPosX{};
	int Enemy_TargetPosY{};

	bool fal = false;

	bool Enemy_IsGrounded = false;
	bool Enemy_IsJumping = false;
	bool Enemy_IsFalling = false;
	double Enemy_JumpTime{};

	//enemy mozgása
	virtual void move(Uint64 dt) = 0;

public:
	Enemy(Properties* props);
	~Enemy();

	//frissíti az adott enemy állapotát
	//dtparaméter  = eltelt idõ az elõzõ frame óta (delta time)
	virtual void Update(Uint64 dt);

	//kirajzolja az adott enemy-t a képernyõre
	virtual void Draw();

	//törli/felszabadítja az adott enemy-t
	virtual void Clean();

	//reseteli az adott enemy-t (jelenleg despawnolja õket)
	virtual void reset();

	//adott enemy támadása
	//virtual void attacking(Uint64 dt) = 0;

	//beállítja az adott enemy-re ható gravitációt
	virtual inline void setGravity(double G) { Enemy_RigidBody->setRigidBody_Gravity(G); }

	//visszaadja az enemy collider boxot
	virtual inline Collider* getCollider() { return Enemy_Collider; }

	//visstaadja, hogy az adott enemy éppen támad-e
	virtual inline bool getAttacking() { return Enemy_IsAttacking; }

	//beállítja a támadás állapotát
	virtual inline void setAttacking(bool e) { Enemy_IsAttacking = e; }

	//visszaadja az adott enemy lehetséges támadási intervallumát pl. 3 másodpercenként támad akkor 3000
	virtual inline double getAttacktime() { return Enemy_AttackTimer; }

	//visszaadja a támadás ereét
	virtual inline int getAttackPower() { return 0; }

	//beállítja a megfelelõ animációt
	virtual void AnimationState() = 0;

	//beállítja a támadás ereét
	virtual inline void setAttackPower(int power) { Enemy_AttackPower = power; }

	//enemy collisionért felelõ fv.
	virtual inline void Enemy_Collision(Uint64 dt);

	//visstaadja a játékos pozícióját
	void getPlayerPosition();

	//visszaadja az inventoryt (azaz semmi)
	//inline void* getInventory() override { return nullptr; }

	//visszaadja a kivalasztott inventory slotot (azaz semmit) 
	inline int getSelectedInventory() { return 0; }

	//--
	void saveInventory() { return; }

	//--
	void readInventory() { return; }

	//beállítja az enemy célpontját
	virtual void setTarget(int X, int Y) { return; }

};

constexpr auto zombieAttacktimer = 1000;

class Zombie : public Enemy{
private:
	
	
public:
	inline Zombie(Properties* props) : Enemy(props) {
		Enemy_AttackPower = 10;
		Enemy_AttackTimer = zombieAttacktimer;
		GameObject_Dimenziok = TextureManager::GetInstance()->getTextureMap()->find("zombie_idle")->second.second;
	};

	//beállítja a megfelelõ animációt
	virtual void AnimationState();

	//mozgásért felelõs fv
	virtual void move(Uint64 dt);

	//támadásért felelõs fv
	virtual bool attacking(Uint64 dt);

	//visszaadja a támadás ereét
	inline int getAttackPower() { return Enemy_AttackPower; }

	//visszaadja a támadás idõzítését
	inline double getAttackTimer() const { return Enemy_AttackTimer; }
};

constexpr auto skeleton_attackTimer = 3000;

class Skeleton : public Enemy{
private:
	bool isAiming = false;
public:
	Skeleton(Properties* props) : Enemy(props) {
		Enemy_AttackTimer = skeleton_attackTimer;
		GameObject_Dimenziok = TextureManager::GetInstance()->getTextureMap()->find("skeleton_idle")->second.second;
	};

	//beállítja a megfelelõ animációt
	virtual void AnimationState();

	//mozgásért felelõs fv
	virtual void move(Uint64 dt);

	//támadásért felelõs fv
	virtual bool attacking(Uint64 dt);
};
