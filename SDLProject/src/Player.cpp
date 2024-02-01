#include <SDL.h>

#include "Player.hpp"
#include "ObjectFactory.hpp"
#include "Input.hpp"
#include "Tiles.hpp"
#include "Engine.hpp"
#include "UI.hpp"


// csinal egy playert es hozza rendeli a PLAYER stringet;
static Registrar < Player > registrar("PLAYER");

Player::Player(Properties* props) : Character(props)
{
	GameObject_hp = props->Properies_hp;

	Player_IsWalking = false;
	Player_IsJumping = false;
	Player_IsFalling = false;
	Player_IsGrounded = false;
	Player_IsAttacking = false;
	Player_IsWalkAttacking = false;
	Player_IsUnderWater = false;

	Player_JumpTime = 0;
	Player_JumpForce = JUMP_FORCE;
	Player_AttackTime = PLAYER_ATTACK_TIME;
	Player_UnderWaterTime = UNDER_WATER_TIME;

	Player_Collider = new Collider();
	Player_Collider->setBuffer(0, 0, 0, 0);

	Player_RigidBody = new RigidBody();
	Player_RigidBody->setRigidBody_Gravity(GRAVITY);

	Player_SpriteAnimation = new SpriteAnimation();
	Player_SpriteAnimation->SetProps(GameObject_TextureID, 0, 6, 100);

	Player_Inventory.fill(std::make_pair(nullptr, 0));
}

void Player::Draw()
{
	Player_SpriteAnimation->Draw(GameObject_Transform->getX(), GameObject_Transform->getY(), GameObject_Width, GameObject_Height, GameObject_Flip);
}

void Player::Update(Uint64 dt)
{
	//std::cout << GameObject_Origin->getX() << std::endl;

	//regen
	regenTimer = regenTimer > 0 ? regenTimer -= dt : 200;
	if (regenTimer == 200){
		GameObject_hp = GameObject_hp < GameObject_MaxHP ? GameObject_hp += 1 : GameObject_hp;
		regenTimer -= dt;
	}
	//regen

	Player_ImunityTime = Player_ImunityTime <= 0 ? 0 : Player_ImunityTime-dt;
	Player_IsWalking = false;
	Player_RigidBody->SetForceToZero();

	//fut jobbra
	if (Input::GetInstance()->getAxisKey(HORIZONTAL) == JOBBRA and !Player_IsAttacking)
	{
		Player_RigidBody->ApplyForceX(JOBBRA * RUN_FORCE);// *dt);
		GameObject_Flip = SDL_FLIP_NONE;
		Player_IsWalking = true;
	}

	//fut balra
	if (Input::GetInstance()->getAxisKey(HORIZONTAL) == BALRA and !Player_IsAttacking)
	{
		Player_RigidBody->ApplyForceX(BALRA * RUN_FORCE);// * dt);
		GameObject_Flip = SDL_FLIP_HORIZONTAL;
		Player_IsWalking = true;
	}

	//scroll
	auto s = Input::GetInstance()->getScroll();
	if (s != 0) {
		if (s < 0) { selectedInventory--; }
		if (s > 0) { selectedInventory++; }
		if (selectedInventory < 0) { selectedInventory = 9; }
		if (selectedInventory > 9) { selectedInventory = 0; }
	}

	//attack
	if ((SDL_BUTTON(Input::GetInstance()->getClickDown()) == 1) or (Input::GetInstance()->getKeyDown(SDL_SCANCODE_K)))
	{
		Player_IsAttacking = true;
		//Player_Animation->setDelta(SDL_GetTicks64());


		//ez itt a blokk felvetel
		auto egerX = UI::GetInstance()->getkepernyoX() / Engine::GetInstance()->getTileSize();
		auto egerY = UI::GetInstance()->getkepernyoY() / Engine::GetInstance()->getTileSize();
		auto colllayer = Engine::GetInstance()->getCollisionLayerVector();
		int tileID = (*colllayer)[egerY][egerX];
		if (tileID != 0) {
			int block_mine_timer = TileData::GetInstance()->getTileDataFromID(tileID)->MineTime;
			if (block_mine_timer >= 0) {
				minetime += dt;
				if (minetime >= block_mine_timer) {
					//auto sajt = new Block(1, "sajt", (*colllayer)[egerY][egerX], 1000);
					auto sajt = ItemData::GetInstance()->getItemByTileID(tileID);
					inventoryplace = 0;
					bool van = false;

					while (inventoryplace < 40) {
						if (Player_Inventory[inventoryplace].second != 0) {
							if (Player_Inventory[inventoryplace].first->getItemID() == sajt->getItemID()) {
								Player_Inventory[inventoryplace].second++;
								break;
							}
						}
						if (Player_Inventory[inventoryplace].second == 0) {
							Player_Inventory[inventoryplace].first = sajt;
							Player_Inventory[inventoryplace].second++;
							break;
						}
						inventoryplace++;
					}



					//kiutott block collider eltuntetese
					(*colllayer)[egerY][egerX] = 0;
					//textura eltuntetese
					(*(*Engine::GetInstance()->getLevelMap()->getMapLayers())[Engine::GetInstance()->getCollisionLayer()]->getTileMap())[egerY][egerX] = 0;
					//if (inventoryplace > 39) { inventoryplace = 0; }
				}
			}
		}
		else {
			minetime = 0;
		}

	}


	//std::cout << SDL_BUTTON(Input::GetInstance()->getClickDown()) << std::endl;
	//jobb click - 8-at terit vissza, mert a 3adik bit lesz az egyes - imo bugos ez a makro de nem akarom megjavitani most...
	if (SDL_BUTTON(Input::GetInstance()->getClickDown()) == 8) {
		auto egerX = UI::GetInstance()->getkepernyoX() / Engine::GetInstance()->getTileSize();
		auto egerY = UI::GetInstance()->getkepernyoY() / Engine::GetInstance()->getTileSize();
		auto colllayer = Engine::GetInstance()->getCollisionLayerVector();
		int tileID = (*colllayer)[egerY][egerX];
		if (tileID == 0) {
			if (Player_Inventory[selectedInventory].second != 0) {
				(*colllayer)[egerY][egerX] = Player_Inventory[selectedInventory].first->getTileID();
				(*(*Engine::GetInstance()->getLevelMap()->getMapLayers())[Engine::GetInstance()->getCollisionLayer()]->getTileMap())[egerY][egerX] = Player_Inventory[selectedInventory].first->getTileID();
				Player_Inventory[selectedInventory].second--;
				if (Player_Inventory[selectedInventory].second == 0) {
					Player_Inventory[selectedInventory].first = nullptr;
				}
			}
		}
	}

	//jobbra fut / ut
	if (Input::GetInstance()->getAxisKey(HORIZONTAL) == JOBBRA and Player_IsAttacking)
	{
		Player_IsWalkAttacking = true;
		Player_RigidBody->ApplyForceX(JOBBRA * RUN_FORCE);// * dt);
		GameObject_Flip = SDL_FLIP_NONE;
	}

	//balra fut / ut
	if (Input::GetInstance()->getAxisKey(HORIZONTAL) == BALRA and Player_IsAttacking)
	{
		Player_IsWalkAttacking = true;
		Player_RigidBody->ApplyForceX(BALRA * RUN_FORCE);// * dt);
		GameObject_Flip = SDL_FLIP_HORIZONTAL;
	}

	//jump
	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_SPACE) and Player_IsGrounded)
	{
		Player_IsJumping = true;
		Player_IsGrounded = false;
		Player_RigidBody->ApplyForceY(FEL * Player_JumpForce);// * static_cast<double>(dt) );
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_SPACE) and Player_IsJumping and Player_JumpTime > 0)
	{
		Player_JumpTime = Player_JumpTime - dt;
		Player_RigidBody->ApplyForceY(FEL * Player_JumpForce);// * static_cast<double>(dt));
	}
	else
	{
		Player_IsJumping = false;
	}

	//zuhanas
	if (Player_RigidBody->getRigidBody_Velocity().getY() > 0 and !Player_IsGrounded)
	{
		Player_IsFalling = true;
	}
	else
	{
		Player_IsFalling = false;
	}

	//attack timer
	if (Player_IsAttacking and Player_AttackTime > 0)
	{
		Player_AttackTime -= dt;
	}
	else
	{
		Player_IsAttacking = false;
		Player_IsWalkAttacking = false;
		Player_AttackTime = PLAYER_ATTACK_TIME;
	}


	//collision
	Player_LastSafePosition.setX(GameObject_Transform->getX());
	GameObject_Transform->setX(GameObject_Transform->getX() + Player_RigidBody->getRigidBody_Position().getX());
	Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), GameObject_Width = TextureManager::GetInstance()->getTextureMap()->find("player_idle")->second.second.w, GameObject_Height);
	//std::cout << GameObject_Width << "\t" << GameObject_Height << "\n";

	if (CollisionHandler::GetInstance()->MapCollision(this, &Player_IsGrounded))
	{
		GameObject_Transform->setX(Player_LastSafePosition.getX());
	}

	Player_LastSafePosition.setY(GameObject_Transform->getY());

	//erre majd ra kell kerdezni...

	//levitalas miatt van itt
	if ((static_cast<int>(Player_LastSafePosition.getY()) % CollisionHandler::GetInstance()->getCollisionLayer()->getTileSize()) >= (CollisionHandler::GetInstance()->getCollisionLayer()->getTileSize() - dt * Player_RigidBody->getGravity())) {

			//int szam = 0;
			//Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()) + dt * Player_RigidBody->getGravity() - szam, 190, 240);
			//while (CollisionHandler::GetInstance()->MapCollision(this, &Player_IsGrounded)) {
			//	//ha mozgatjuk az ablakot a szamlalo felmegy...
			//	szam += 1;
			//	std::cout << szam << "\n";
			//	Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()) + dt * Player_RigidBody->getGravity() - szam, 190, 240);
			//	if (szam > CollisionHandler::GetInstance()->getTileSize()) { break; }
			//}
			//Player_LastSafePosition.setY(GameObject_Transform->getY() + dt * Player_RigidBody->getGravity() - szam);
		
		auto szam = ((static_cast<int>(Player_LastSafePosition.getY()) + GameObject_Height) % CollisionHandler::GetInstance()->getCollisionLayer()->getTileSize());
		//std::cout << szam << std::endl;
		Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()) + dt * Player_RigidBody->getGravity() - szam, GameObject_Width = TextureManager::GetInstance()->getTextureMap()->find("player_idle")->second.second.w, GameObject_Height);
		if (CollisionHandler::GetInstance()->MapCollision(this, &Player_IsGrounded))
		{
			GameObject_Transform->setX(Player_LastSafePosition.getX());
		}
		Player_LastSafePosition.setY(GameObject_Transform->getY());
	}

	GameObject_Transform->setY(GameObject_Transform->getY() + Player_RigidBody->getRigidBody_Position().getY());
	Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), GameObject_Width = TextureManager::GetInstance()->getTextureMap()->find("player_idle")->second.second.w, GameObject_Height);

	if (CollisionHandler::GetInstance()->MapCollision(this, &Player_IsGrounded))
	{
		if (Player_IsGrounded) {
			Player_JumpTime = JUMP_TIME;
		}
		GameObject_Transform->setY(Player_LastSafePosition.getY());
	}
	else
	{
		Player_IsGrounded = false;
	}

	//viz alatt
	if (getPGravity() < 1.0) {
		Player_IsUnderWater = true;
		Player_UnderWaterTime -= dt;
		if (Player_UnderWaterTime < 0 and Player_ImunityTime <= 0) {
			GameObject_hp -= 1;
			Player_ImunityTime = 50;
		}
	}
	else {
		Player_IsUnderWater = false;
		Player_UnderWaterTime = UNDER_WATER_TIME;
	}

	//ehhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
	GameObject_Origin->setX(GameObject_Transform->getX()/* + GameObject_Width / 2.0*/);
	GameObject_Origin->setY(GameObject_Transform->getY()/* + GameObject_Height / 2.0*/);

	AnimationState();
	Player_RigidBody->Update(dt);
	Player_SpriteAnimation->Update(dt);
}

void Player::AnimationState()
{
	Player_SpriteAnimation->SetProps("player_idle", 0, 4, 400);
	GameObject_Width = TextureManager::GetInstance()->getTextureMap()->find("player_idle")->second.second.w;
	GameObject_Height = TextureManager::GetInstance()->getTextureMap()->find("player_idle")->second.second.h;

	if (Player_IsWalking) {
		Player_SpriteAnimation->SetProps("player_walking", 0, 6, 500);
		GameObject_Width = TextureManager::GetInstance()->getTextureMap()->find("player_walking")->second.second.w;
		GameObject_Height = TextureManager::GetInstance()->getTextureMap()->find("player_walking")->second.second.h;
	}

	if (Player_IsFalling or !Player_IsGrounded) {
		Player_SpriteAnimation->SetProps("player_jumping", 0, 1, 1);
		GameObject_Width = TextureManager::GetInstance()->getTextureMap()->find("player_jumping")->second.second.w;
		GameObject_Height = TextureManager::GetInstance()->getTextureMap()->find("player_jumping")->second.second.h;
	}

	if (Player_IsAttacking) {
		Player_SpriteAnimation->SetProps("player_stand_hit", 0, 4, PLAYER_ATTACK_TIME / Player_SpriteAnimation->getFrameCount(), true);
		GameObject_Width = TextureManager::GetInstance()->getTextureMap()->find("player_stand_hit")->second.second.w;
		GameObject_Height = TextureManager::GetInstance()->getTextureMap()->find("player_stand_hit")->second.second.h;
	}

	if (Player_IsWalkAttacking) {
		Player_SpriteAnimation->SetProps("player_walk_hit", 0, 4, PLAYER_ATTACK_TIME / Player_SpriteAnimation->getFrameCount(), true);
		GameObject_Width = TextureManager::GetInstance()->getTextureMap()->find("player_walk_hit")->second.second.w;
		GameObject_Height = TextureManager::GetInstance()->getTextureMap()->find("player_walk_hit")->second.second.h;
	}

}

void Player::Clean()
{
	TextureManager::GetInstance()->Drop(GameObject_TextureID);
}

void Player::reset()
{
	GameObject_hp = 100;
	GameObject_Transform->setX(0);
	GameObject_Transform->setY(0);
}

void Player::setSelectedInventory()
{
}
