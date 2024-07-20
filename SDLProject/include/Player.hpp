#pragma once

#include "array"
#include "Character.hpp"
#include "Itemdata.hpp"
#include "RigidBody.hpp"
#include "SpriteAnimation.hpp"
#include "Timer.hpp"

//az ido ms
//ezek kesobb lehetnek az osztalyban is, ha valamin buffolni akarunk
//vagy marad ez az alap és a bubb item csak egy szorzo lesz
constexpr auto JUMP_TIME = 200.0;
constexpr auto JUMP_FORCE = 3.0;
constexpr auto RUN_FORCE = 1.0;
constexpr auto UNDER_WATER_TIME = 10000.0;
constexpr auto PLAYER_ATTACK_TIME = 300.0;
constexpr auto PLAYER_ATTACK_POWER = 15;
constexpr auto POTION_CD = 60000;

class Player : public Character {
private:
	bool Player_IsWalking;
	bool Player_IsJumping;
	bool Player_IsFalling;
	bool Player_IsGrounded;
	bool Player_IsAttacking;
	bool Player_IsWalkAttacking;

	double Player_JumpForce;

	double regenTimer = 1000.0;
	double potiTimer = POTION_CD;

	bool Player_IsUnderWater{};
	double Player_UnderWaterTime{};
	double Player_ImunityTime{};

	//short aniState;


	bool PlayerReadyAttacking{};
	double Player_JumpTime;
	double Player_AttackTime;
	int Player_AttackPower = 0;
	double minetime = 0;

	Collider Player_Collider;
	SpriteAnimation Player_SpriteAnimation;
	RigidBody Player_RigidBody;
	Vector2D Player_LastSafePosition;

	int inventoryplace = 0;
	std::array<std::pair<Item*, int>, 40> Player_Inventory;
	int selectedInventory = 0;

	//animáció állapotának meghatározása
	virtual void AnimationState() override;
public:

	Player(Properties* props);
	//~Player();

	//visszaadja a player merevtestét
	inline RigidBody* getPlayerBody() { return &Player_RigidBody; }

	//beállítja, hogy a player víz (vagy egyéb) folyadékban vagy hasonló blokkban van-e
	inline void setUnderWater(bool e) { Player_IsUnderWater = e; }

	//visszadja a player collidert
	virtual inline Collider* getCollider() override { return &Player_Collider; }


	virtual inline void setAttacking(bool e) override {}; // csak enemy hasznalja
	virtual inline bool attacking(Uint64 dt) override { return false; } // ezt is

	//kiír
	virtual void Draw() override;

	//frissít
	virtual void Update(Uint64 dt) override;

	//töröl felszabadít
	virtual void Clean() override;

	//reset
	virtual void reset() override;

	//playerre ható gravitáció beállítása
	virtual inline void setGravity(double G) override { Player_RigidBody.setRigidBody_Gravity(G); }

	//
	virtual inline double getAttacktime() override { return Player_AttackTime; }

	//visszaadja az ütés ereét
	virtual inline int getAttackPower() override { return Player_AttackPower; }

	//beállítja az ütés ereét
	virtual inline void setAttackPower(int power) override { Player_AttackPower = power; }

	//visszaadja, hogy a player támad-e
	virtual inline bool getAttacking() override { return PlayerReadyAttacking; }

	//visszaadja a playerre ható gravitációt
	inline double getPGravity() { return Player_RigidBody.getGravity(); }

	//visszaadja a player inventory-t
	inline void* getInventory() override { return &Player_Inventory; }

	//visszadja a kiválasztott inventory slotot
	inline int getSelectedInventory() { return selectedInventory; }


	//inventory mentése fájlba
	void saveInventory();

	//inventory beolvasása fájlból
	void readInventory();

	//itt nincs jelentõsége
	virtual void setTarget(int X, int Y) override { return; }

	inline double getPotionDebuff() { return potiTimer; }
};