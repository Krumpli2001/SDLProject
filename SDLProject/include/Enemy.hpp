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

	//enemy mozg�sa
	virtual void move(Uint64 dt) = 0;

public:
	Enemy(Properties* props);
	~Enemy();

	//friss�ti az adott enemy �llapot�t
	//dtparam�ter  = eltelt id� az el�z� frame �ta (delta time)
	virtual void Update(Uint64 dt);

	//kirajzolja az adott enemy-t a k�perny�re
	virtual void Draw();

	//t�rli/felszabad�tja az adott enemy-t
	virtual void Clean();

	//reseteli az adott enemy-t (jelenleg despawnolja �ket)
	virtual void reset();

	//adott enemy t�mad�sa
	//virtual void attacking(Uint64 dt) = 0;

	//be�ll�tja az adott enemy-re hat� gravit�ci�t
	virtual inline void setGravity(double G) { Enemy_RigidBody->setRigidBody_Gravity(G); }

	//visszaadja az enemy collider boxot
	virtual inline Collider* getCollider() { return Enemy_Collider; }

	//visstaadja, hogy az adott enemy �ppen t�mad-e
	virtual inline bool getAttacking() { return Enemy_IsAttacking; }

	//be�ll�tja a t�mad�s �llapot�t
	virtual inline void setAttacking(bool e) { Enemy_IsAttacking = e; }

	//visszaadja az adott enemy lehets�ges t�mad�si intervallum�t pl. 3 m�sodpercenk�nt t�mad akkor 3000
	virtual inline double getAttacktime() { return Enemy_AttackTimer; }

	//visszaadja a t�mad�s ere�t
	virtual inline int getAttackPower() { return 0; }

	//be�ll�tja a megfelel� anim�ci�t
	virtual void AnimationState() = 0;

	//be�ll�tja a t�mad�s ere�t
	virtual inline void setAttackPower(int power) { Enemy_AttackPower = power; }

	//enemy collision�rt felel� fv.
	virtual inline void Enemy_Collision(Uint64 dt);

	//visstaadja a j�t�kos poz�ci�j�t
	void getPlayerPosition();

	//visszaadja az inventoryt (azaz semmi)
	//inline void* getInventory() override { return nullptr; }

	//visszaadja a kivalasztott inventory slotot (azaz semmit) 
	inline int getSelectedInventory() { return 0; }

	//--
	void saveInventory() { return; }

	//--
	void readInventory() { return; }

	//be�ll�tja az enemy c�lpontj�t
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

	//be�ll�tja a megfelel� anim�ci�t
	virtual void AnimationState();

	//mozg�s�rt felel�s fv
	virtual void move(Uint64 dt);

	//t�mad�s�rt felel�s fv
	virtual bool attacking(Uint64 dt);

	//visszaadja a t�mad�s ere�t
	inline int getAttackPower() { return Enemy_AttackPower; }

	//visszaadja a t�mad�s id�z�t�s�t
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

	//be�ll�tja a megfelel� anim�ci�t
	virtual void AnimationState();

	//mozg�s�rt felel�s fv
	virtual void move(Uint64 dt);

	//t�mad�s�rt felel�s fv
	virtual bool attacking(Uint64 dt);
};
