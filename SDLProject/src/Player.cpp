#include <fstream>

#include <SDL.h>
#include <tinyxml.h>

#include "Engine.hpp"
#include "Input.hpp"
#include "ItemData.hpp"
#include "ObjectFactory.hpp"
#include "Player.hpp"
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

	Player_RigidBody = new RigidBody();
	Player_RigidBody->setRigidBody_Gravity(GRAVITY);

	Player_SpriteAnimation = new SpriteAnimation();
	Player_SpriteAnimation->SetProps(GameObject_TextureID, 0, 0, 0);

	Player_Inventory.fill(std::make_pair(nullptr, 0));
}

Player::~Player()
{
	delete Player_Collider;
	delete Player_RigidBody;
	delete Player_SpriteAnimation;
}



void Player::Draw()
{
	constexpr auto angle = 0;
	constexpr auto scale = 1;
	Player_SpriteAnimation->Draw(GameObject_Transform->getX(), GameObject_Transform->getY(), GameObject_Width, GameObject_Height, GameObject_Flip , angle, scale, GameObject_Dimenziok.w, GameObject_Dimenziok.h);
}

void Player::Update(Uint64 dt)
{
	aniState = playerAniState::PlayerIsIdle;

	auto texturemanagerInstance = TextureManager::GetInstance();

	if (GameObject_Dimenziok.w == 0 and GameObject_Dimenziok.h == 0) {
		GameObject_Dimenziok = texturemanagerInstance->getTextureMap()->find("player_idle")->second.second;
	}

	//regen
	constexpr auto RTime = 1000;
	regenTimer = regenTimer > 0 ? regenTimer -= dt : RTime;
	if (regenTimer == RTime){
		GameObject_hp = GameObject_hp < GameObject_MaxHP ? GameObject_hp += 1 : GameObject_hp;
		regenTimer -= dt;
	}
	//regen

	Player_ImunityTime = Player_ImunityTime <= 0 ? 0 : Player_ImunityTime-dt;
	potiTimer = potiTimer < POTION_CD and potiTimer > 0 ? potiTimer - dt : POTION_CD;

	Player_IsWalking = false;
	Player_RigidBody->SetForceToZero();

	if (GameObject_kbt > 0) {
		texturemanagerInstance->setTextColor(texturemanagerInstance->getTextureMap()->find(*Player_SpriteAnimation->getSpriteID())->second.first, "red");
		GameObject_kbt = static_cast<int>(GameObject_kbt - dt);

		Player_RigidBody->ApplyForceY(FEL * GameObject_kb);
		Player_RigidBody->ApplyForceX(Gameobject_kb_direction * GameObject_kb);
		Player_IsJumping = true;
		Player_IsGrounded = false;
		
	}
	else {
		texturemanagerInstance->setTextColor(texturemanagerInstance->getTextureMap()->find(*Player_SpriteAnimation->getSpriteID())->second.first, "white");
	}
	GameObject_kbt = GameObject_kbt < INT_MIN / 2 ? 0 : GameObject_kbt;

	auto inputInstance = Input::GetInstance();

	//fut jobbra
	if (inputInstance->getAxisKey(HORIZONTAL) == JOBBRA and !Player_IsAttacking)
	{
		Player_RigidBody->ApplyForceX(JOBBRA * RUN_FORCE);
		GameObject_Flip = SDL_FLIP_NONE;
		//Player_IsWalking = true;
		aniState = playerAniState::PlayerIsWalking;
	}

	//fut balra
	if (inputInstance->getAxisKey(HORIZONTAL) == BALRA and !Player_IsAttacking)
	{
		Player_RigidBody->ApplyForceX(BALRA * RUN_FORCE);
		GameObject_Flip = SDL_FLIP_HORIZONTAL;
		//Player_IsWalking = true;
		aniState = playerAniState::PlayerIsWalking;
	}

	//scroll
	auto s = inputInstance->getScroll();
	if (s != 0) {
		if (s < 0) { selectedInventory--; }
		if (s > 0) { selectedInventory++; }
		if (selectedInventory < 0) { selectedInventory = 9; }
		if (selectedInventory > 9) { selectedInventory = 0; }
	}

	//attack
	if ((SDL_BUTTON(inputInstance->getClickDown()) == 1) or (inputInstance->getKeyDown(SDL_SCANCODE_K)))
	{
		Player_IsAttacking = true;
		//aniState = playerAniState::PlayerIsAttacking;

		auto uiInstance = UI::GetInstance();
		auto engineInstance = Engine::GetInstance();

		//ez itt a blokk felvetel
		auto egerX = uiInstance->getkepernyoX() / engineInstance->getTileSize();
		egerX = egerX < 0 ? 0 : egerX;
		egerX = egerX > engineInstance->getMap_W()/ engineInstance->getTileSize() ? engineInstance->getMap_W()/engineInstance->getTileSize() : egerX;
		auto egerY = uiInstance->getkepernyoY() / engineInstance->getTileSize();
		egerY = egerY < 0 ? 0 : egerY;
		egerY = egerY > engineInstance->getMap_H() / engineInstance->getTileSize() ? engineInstance->getMap_H() / engineInstance->getTileSize() : egerY;
		auto colllayer = engineInstance->getCollisionLayerVector();
		int tileID = (*colllayer)[egerY][egerX];
		if (tileID != 0) {
			uint32_t block_mine_timer = ItemData::GetInstance()->getTileDataFromID(tileID)->MineTime;
			//igy csak az a bak ha athuzod masik blockra akkor is hozzaadja a timerhez
			if (block_mine_timer >= 0) {
				minetime += dt;
				if (minetime >= block_mine_timer) {
					auto sajt = ItemData::GetInstance()->getItemByID(tileID);
					inventoryplace = 0;
					bool van = false;

					bool found = false;

					while (inventoryplace < 40) {
						if (Player_Inventory[inventoryplace].first != nullptr) {
							if (Player_Inventory[inventoryplace].first->getItemID() == sajt->getItemID()) {
								found = true;
								Player_Inventory[inventoryplace].second++;
								
							}
						}
						inventoryplace++;
					}
						inventoryplace = 0;

					if (!found) {
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
					}


					//kiutott block collider eltuntetese
					(*colllayer)[egerY][egerX] = 0;
				}
			}
		}
		else {
			minetime = 0;
		}

		//csak itt van dynamic cast, leginkabb kivancsisagbol
		if (Player_Inventory[selectedInventory].second != 0 and Player_Inventory[selectedInventory].first->getType() == tipus::tool) {
				auto tool = dynamic_cast<Tool*>(Player_Inventory[selectedInventory].first);
				if (tool->getAttackPower() > 0) {
					Player_AttackPower = tool->getAttackPower();
				}
				else {
					Player_AttackPower = PLAYER_ATTACK_POWER;
				}

				if (tool->getHealing() > 0) {
					if (tool->getCons(), potiTimer==POTION_CD) {
						GameObject_hp += tool->getHealing();
						GameObject_hp = GameObject_hp > GameObject_MaxHP ? GameObject_MaxHP : GameObject_hp;
						if (tool->getCons()) {
							Player_Inventory[selectedInventory].second--;
						}
						potiTimer -= dt;
					}
					if (Player_Inventory[selectedInventory].second <= 0) {
						Player_Inventory[selectedInventory].first = nullptr;
					}
				}
			
		}

	}


	//std::cout << SDL_BUTTON(Input::GetInstance()->getClickDown()) << std::endl;
	//jobb click - 8-at terit vissza, mert a 3adik bit lesz az egyes - imo bugos ez a makro de nem akarom megjavitani most...
	if (SDL_BUTTON(inputInstance->getClickDown()) == 8) {

		auto uiInstance = UI::GetInstance();
		auto engineInstance = Engine::GetInstance();

		auto egerX = uiInstance->getkepernyoX() / engineInstance->getTileSize();
		auto egerY = uiInstance->getkepernyoY() / engineInstance->getTileSize();
		auto colllayer = engineInstance->getCollisionLayerVector();
		int tileID = (*colllayer)[egerY][egerX];
		if (tileID == 0 and !CollisionHandler::GetInstance()->CheckCollision(*Player_Collider->getBox(),
			{egerX * engineInstance->getTileSize(), egerY * engineInstance->getTileSize(), engineInstance->getTileSize(), engineInstance->getTileSize()}
		))
		{
			if (uiInstance->getTransfer()->first!=nullptr and uiInstance->getTransfer()->first->getType() == tipus::block) {
				(*colllayer)[egerY][egerX] = uiInstance->getTransfer()->first->getItemID();
				uiInstance->getTransfer()->second--;
				if (uiInstance->getTransfer()->second <= 0) {
					uiInstance->getTransfer()->first = nullptr;
				}
			}
			else if (Player_Inventory[selectedInventory].second != 0 and Player_Inventory[selectedInventory].first->getType() == tipus::block) {
				(*colllayer)[egerY][egerX] = Player_Inventory[selectedInventory].first->getItemID();
				Player_Inventory[selectedInventory].second--;
				if (Player_Inventory[selectedInventory].second <= 0) {
					Player_Inventory[selectedInventory].first = nullptr;
				}
			}
		}
	}

	//jobbra fut / ut
	if (inputInstance->getAxisKey(HORIZONTAL) == JOBBRA and Player_IsAttacking)
	{
		//aniState = playerAniState::PlayerIsWalkingAndAttacking;
		//Player_IsWalkAttacking = true;
		Player_RigidBody->ApplyForceX(JOBBRA * RUN_FORCE);// * dt);
		GameObject_Flip = SDL_FLIP_NONE;
	}

	//balra fut / ut
	if (inputInstance->getAxisKey(HORIZONTAL) == BALRA and Player_IsAttacking)
	{
		//aniState = playerAniState::PlayerIsWalkingAndAttacking;
		//Player_IsWalkAttacking = true;
		Player_RigidBody->ApplyForceX(BALRA * RUN_FORCE);// * dt);
		GameObject_Flip = SDL_FLIP_HORIZONTAL;
	}

	//jump
	if (inputInstance->getKeyDown(SDL_SCANCODE_SPACE) and Player_IsGrounded)
	{
		Player_IsJumping = true;
		Player_IsGrounded = false;
		Player_RigidBody->ApplyForceY(FEL * Player_JumpForce);
	}

	if (inputInstance->getKeyDown(SDL_SCANCODE_SPACE) and Player_IsJumping and Player_JumpTime > 0)
	{
		Player_JumpTime = Player_JumpTime - dt;
		Player_RigidBody->ApplyForceY(FEL * Player_JumpForce);
	}
	else
	{
		Player_IsJumping = false;
	}

	//zuhanas
	if (Player_RigidBody->getRigidBody_Velocity().getY() > 0 and !Player_IsGrounded)
	{
		Player_IsFalling = true;
		aniState = playerAniState::PlayerIsFalling;
	}
	else
	{
		Player_IsFalling = false;
	}

	//attack timer
	if (Player_IsAttacking and Player_AttackTime == PLAYER_ATTACK_TIME)
	{
		PlayerReadyAttacking = true;
		Player_AttackTime -= dt;
	}
	else
	{
		PlayerReadyAttacking = false;
		
		//Player_AttackTime-=dt;
		Player_AttackTime = Player_AttackTime < PLAYER_ATTACK_TIME && Player_AttackTime>0 ? Player_AttackTime -= dt : PLAYER_ATTACK_TIME;

		if (Player_AttackTime == PLAYER_ATTACK_TIME) {
			Player_IsAttacking = false;
			//Player_IsWalkAttacking = false;
		}
		else {
			Player_IsAttacking = true;
			//Player_IsWalkAttacking = true;
		}
		
	}


	//collision
	Player_LastSafePosition.setX(GameObject_Transform->getX());
	GameObject_Transform->setX(GameObject_Transform->getX() + Player_RigidBody->getRigidBody_Position().getX());
	Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), GameObject_Dimenziok.w, GameObject_Dimenziok.h);

	auto collhandlerInstance = CollisionHandler::GetInstance();

	if (collhandlerInstance->MapCollision(this, &Player_IsGrounded))
	{
		GameObject_Transform->setX(Player_LastSafePosition.getX());
	}



	Player_LastSafePosition.setY(GameObject_Transform->getY());

	//erre majd ra kell kerdezni...

	//levitalas miatt van itt
	if ((static_cast<int>(Player_LastSafePosition.getY()) % collhandlerInstance->getCollisionLayer()->getTileSize()) >= (collhandlerInstance->getCollisionLayer()->getTileSize() - dt * Player_RigidBody->getGravity())) {
		
		auto szam = ((static_cast<int>(Player_LastSafePosition.getY()) + GameObject_Height) % collhandlerInstance->getCollisionLayer()->getTileSize());
		Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY() + dt * Player_RigidBody->getGravity() - szam), GameObject_Dimenziok.w, GameObject_Dimenziok.h);
		if (collhandlerInstance->MapCollision(this, &Player_IsGrounded))
		{
			GameObject_Transform->setX(Player_LastSafePosition.getX());
		}
		Player_LastSafePosition.setY(GameObject_Transform->getY());
	}

	GameObject_Transform->setY(GameObject_Transform->getY() + Player_RigidBody->getRigidBody_Position().getY());
	Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), GameObject_Dimenziok.w, GameObject_Dimenziok.h);

	if (collhandlerInstance->MapCollision(this, &Player_IsGrounded))
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

	GameObject_Origin->setX(GameObject_Transform->getX() + GameObject_Dimenziok.w);
	GameObject_Origin->setY(GameObject_Transform->getY() + GameObject_Dimenziok.h);

	AnimationState();
	Player_RigidBody->Update(dt);
	Player_SpriteAnimation->Update(dt);
}

void Player::AnimationState()
{
	auto texturemanagerInstance = TextureManager::GetInstance();
	if (aniState == playerAniState::PlayerIsIdle) {
		Player_SpriteAnimation->SetProps("player_idle", 0, 4, 400);
		GameObject_Width = texturemanagerInstance->getTextureMap()->find("player_idle")->second.second.w;
		GameObject_Height = texturemanagerInstance->getTextureMap()->find("player_idle")->second.second.h;
	}

	if (aniState == playerAniState::PlayerIsWalking) {
		Player_SpriteAnimation->SetProps("player_walking", 0, 6, 500);
		GameObject_Width = texturemanagerInstance->getTextureMap()->find("player_walking")->second.second.w;
		GameObject_Height = texturemanagerInstance->getTextureMap()->find("player_walking")->second.second.h;
	}

	if (Player_IsFalling or !Player_IsGrounded) {
		Player_SpriteAnimation->SetProps("player_jumping", 0, 1, 1);
		GameObject_Width = texturemanagerInstance->getTextureMap()->find("player_jumping")->second.second.w;
		GameObject_Height = texturemanagerInstance->getTextureMap()->find("player_jumping")->second.second.h;
	}

	if (aniState == playerAniState::PlayerIsAttacking or Player_IsAttacking) {
		Player_SpriteAnimation->SetProps("player_stand_hit", 0, 4, static_cast<int>(PLAYER_ATTACK_TIME / Player_SpriteAnimation->getFrameCount()), true);
		GameObject_Width = texturemanagerInstance->getTextureMap()->find("player_stand_hit")->second.second.w;
		GameObject_Height = texturemanagerInstance->getTextureMap()->find("player_stand_hit")->second.second.h;
	}

	if (aniState == playerAniState::PlayerIsWalking and Player_IsAttacking) {
		Player_SpriteAnimation->SetProps("player_walk_hit", 0, 4, static_cast<int>(PLAYER_ATTACK_TIME / Player_SpriteAnimation->getFrameCount()), true);
		GameObject_Width = texturemanagerInstance->getTextureMap()->find("player_walk_hit")->second.second.w;
		GameObject_Height = texturemanagerInstance->getTextureMap()->find("player_walk_hit")->second.second.h;
		//std::cout << 'b';
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

void Player::saveInventory()
{
	std::string str = "saves/" + Engine::GetInstance()->getMapName() + ".xml";
	std::ofstream f(str);
	if (f.is_open()) {
		f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		f << "<player>\n";
		f << "<coords X=\"" << GameObject_Transform->getX() << "\" Y=\"" << GameObject_Transform->getY() << "\" />\n";
		for (int i = 0; i < Player_Inventory.size(); i++) {
			if (Player_Inventory[i].first) {
				f << "<slot ItemID=\"" << Player_Inventory[i].first->getItemID() << "\" Amount=\"" << Player_Inventory[i].second << "\" />\n";
			}
			else {
				f << "<slot ItemID=\"" << 0 << "\" Amount=\"" << 0 << "\" />\n";
			}
		}
		f << "</player>\n";
		f.close();
	}
}

void Player::readInventory()
{
	TiXmlDocument xml;
	auto engineInstance = Engine::GetInstance();
	std::string source = "saves/" + engineInstance->getMapName() + ".xml";
	xml.LoadFile(source);
	if (xml.Error()) {

		std::cout << "Failde to load: " << source << std::endl;
		std::cout << "setting to default loc\n";
		GameObject_Transform->setX(engineInstance->getMap_W() / 2);
		GameObject_Transform->setY(engineInstance->legmamasabbBlock(static_cast<int>(GameObject_Transform->getX()) - TextureManager::GetInstance()->getTextureMap()->find("player_idle")->second.second.w));
		return;
	}
	TiXmlElement* root = xml.RootElement();
	
	int i = 0;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("coords")) {
			GameObject_Transform->setX(std::stoi(e->Attribute("X")));
			GameObject_Transform->setY(std::stoi(e->Attribute("Y")));
		}
		if (e->Value() == std::string("slot")) {
			int ItemID = std::stoi(e->Attribute("ItemID"));
			int Amount = std::stoi(e->Attribute("Amount"));

			if (Amount > 0) {
				Player_Inventory[i].first = ItemData::GetInstance()->getItemByID(ItemID);
				Player_Inventory[i].second = Amount;
			}
			i++;
		}
	}
}
