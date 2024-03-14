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
#define UNDER_WATER_TIME 10000.0

enum playerAniState {
	PlayerIsIdle,
	PlayerIsWalking,
	PlayerIsJumping,
	PlayerIsFalling,
	PlayerIsAttacking,
	PlayerIsWalkingAndAttacking,
};

class Player : public Character {
private:
	bool Player_IsWalking;
	bool Player_IsJumping;
	bool Player_IsFalling;
	bool Player_IsGrounded;
	bool Player_IsAttacking;
	bool Player_IsWalkAttacking;

	double Player_JumpForce;

	double regenTimer = 200.0;

	bool Player_IsUnderWater{};
	double Player_UnderWaterTime{};

	double Player_ImunityTime{};

	//short aniState;


	bool PlayerReadyAttacking;
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

	//animáció állapotának meghatározása
	void AnimationState();
public:

	Player(Properties* props);
	~Player();

	//visszaadja a player merevtestét
	inline RigidBody* getPlayerBody() { return Player_RigidBody; }

	//beállítja, hogy a player víz (vagy egyéb) folyadékban vagy hasonló blokkban van-e
	inline void setUnderWater(bool e) { Player_IsUnderWater = e; }

	//visszadja a player collidert
	virtual inline Collider* getCollider() { return Player_Collider; }


	virtual inline void setAttacking(bool e) {}; // csak enemy hasznalja
	virtual inline void attacking(Uint64 dt) {}; // ezt is

	//kiír
	virtual void Draw();

	//frissít
	virtual void Update(Uint64 dt);

	//töröl felszabadít
	virtual void Clean();

	//reset
	virtual void reset();

	//playerre ható gravitáció beállítása
	virtual inline void setGravity(double G) { Player_RigidBody->setRigidBody_Gravity(G); }

	//
	virtual inline double getAttacktime() { return Player_AttackTime; }

	//visszaadja az ütés ereét
	virtual inline int getAttackPower() { return Player_AttackPower; }

	//beállítja az ütés ereét
	virtual inline void setAttackPower(int power) { Player_AttackPower = power; }

	//visszaadja, hogy a player támad-e
	virtual inline bool getAttacking() { return PlayerReadyAttacking; }

	//visszaadja a playerre ható gravitációt
	inline double getPGravity() { return Player_RigidBody->getGravity(); }

	//wow lehet ilyet is - ez rettenet buta lmao

	//visszaadja a player inventory-t
	inline void* getInventory() override { return &Player_Inventory; }

	//visszadja a kiválasztott inventory slotot
	inline int getSelectedInventory() { return selectedInventory; }


	//inventory mentése fájlba
	void saveInventory();

	//inventory beolvasása fájlból
	void readInventory();

	//itt nincs jelentõsége
	virtual void setTarget(int X, int Y) { return; }
};