#pragma once

#include "Character.hpp"
#include "SpriteAnimation.hpp"
#include "RigidBody.hpp"
#include "Timer.hpp"
#include "Itemdata.hpp"
#include "array"

//az ido ms
#define JUMP_TIME 200.0
#define JUMP_FORCE 3.0
#define RUN_FORCE 1.0
#define UNDER_WATER_TIME 10000

class Player : public Character {
private:
	bool Player_IsWalking;
	bool Player_IsJumping;
	bool Player_IsFalling;
	bool Player_IsGrounded;
	bool Player_IsAttacking;
	bool Player_IsWalkAttacking;

	double Player_JumpForce;

	double regenTimer = 200;

	bool Player_IsUnderWater{};
	double Player_UnderWaterTime{};

	double Player_ImunityTime{};

	double Player_JumpTime;
	double Player_AttackTime;
	int Player_AttackPower = 15;
	double minetime = 0;

	Collider* Player_Collider;
	SpriteAnimation* Player_SpriteAnimation;
	RigidBody* Player_RigidBody;
	Vector2D Player_LastSafePosition;

	int inventoryplace = 0;
	std::array<std::pair<Item*, int>, 40> Player_Inventory;
	int selectedInventory = 0;

	dimenziok Player_Dimenziok{ 0,0 };

	//anim�ci� �llapot�nak meghat�roz�sa
	void AnimationState();
public:

	Player(Properties* props);

	//visszaadja a player merevtest�t
	inline RigidBody* getPlayerBody() { return Player_RigidBody; }

	//be�ll�tja, hogy a player v�z (vagy egy�b) folyad�kban vagy hasonl� blokkban van-e
	inline void setUnderWater(bool e) { Player_IsUnderWater = e; }

	//visszadja a player collidert
	virtual inline Collider* getCollider() { return Player_Collider; }


	virtual inline void setAttacking(bool e) {}; // csak enemy hasznalja
	virtual inline void attacking(Uint64 dt) {}; // ezt is

	//ki�r
	virtual void Draw();

	//friss�t
	virtual void Update(Uint64 dt);

	//t�r�l felszabad�t
	virtual void Clean();

	//reset
	virtual void reset();

	//playerre hat� gravit�ci� be�ll�t�sa
	virtual inline void setGravity(double G) { Player_RigidBody->setRigidBody_Gravity(G); }

	//
	virtual inline double getAttacktime() { return Player_AttackTime; }

	//visszaadja az �t�s ere�t
	virtual inline int getAttackPower() { return Player_AttackPower; }

	//be�ll�tja az �t�s ere�t
	virtual inline void setAttackPower(int power) { Player_AttackPower = power; }

	//visszaadja, hogy a player t�mad-e
	virtual inline bool getAttacking() { return Player_IsAttacking; }

	//visszaadja a playerre hat� gravit�ci�t
	inline double getPGravity() { return Player_RigidBody->getGravity(); }

	//wow lehet ilyet is - ez rettenet buta lmao

	//visszaadja a player inventory-t
	inline void* getInventory() override { return &Player_Inventory; }

	//visszadja a kiv�lasztott inventory slotot
	inline int getSelectedInventory() { return selectedInventory; }


	//inventory ment�se f�jlba
	void saveInventory();

	//inventory beolvas�sa f�jlb�l
	void readInventory();

	//itt nincs jelent�s�ge
	virtual void setTarget(int X, int Y) { return; }
};