#include <SDL.h>

#include "Player.hpp"
#include "ObjectFactory.hpp"
#include "Input.hpp"


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
}

void Player::Draw(double scale)
{
	Player_SpriteAnimation->Draw(GameObject_Transform->getX(), GameObject_Transform->getY(), GameObject_Width, GameObject_Height, GameObject_Flip, scale);
}

void Player::Update(Uint64 dt)
{

	GameObject_hp = GameObject_hp < GameObject_MaxHP ? GameObject_hp += 1 : GameObject_hp;
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

	//attack
	if ((Input::GetInstance()->getClickDown() == 1) or (Input::GetInstance()->getKeyDown(SDL_SCANCODE_K)))
		//if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_K))
	{
		Player_IsAttacking = true;
		//Player_Animation->setDelta(SDL_GetTicks64());
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
	Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 190, 240);


	if (CollisionHandler::GetInstance()->MapCollision(this, &Player_IsGrounded))
	{
		GameObject_Transform->setX(Player_LastSafePosition.getX());
	}

	Player_LastSafePosition.setY(GameObject_Transform->getY());

	//erre majd ra kell kerdezni...

	//levitalas miatt van itt
	if ((static_cast<int>(Player_LastSafePosition.getY()) % CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize()) >= (CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize() - dt * Player_RigidBody->getGravity())) {
		//if (CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize() - dt * Player_RigidBody->getGravity() < 0) {
			int szam = 0;
			Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()) + dt * Player_RigidBody->getGravity() - szam, 190, 240);
			while (CollisionHandler::GetInstance()->MapCollision(this, &Player_IsGrounded)) {
				szam += 1;
				Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()) + dt * Player_RigidBody->getGravity() - szam, 190, 240);
			}
			Player_LastSafePosition.setY(GameObject_Transform->getY() + dt * Player_RigidBody->getGravity() - szam);
		
		//ez jo
		//Player_LastSafePosition.setY(GameObject_Transform->getY() + ((CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize() )) - (static_cast<int>(Player_LastSafePosition.getY()) % CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize()));
	}

	GameObject_Transform->setY(GameObject_Transform->getY() + Player_RigidBody->getRigidBody_Position().getY());
	Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 190, 240);

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

	GameObject_Origin->setX(GameObject_Transform->getX() + GameObject_Width / 2.0);
	GameObject_Origin->setY(GameObject_Transform->getY() + GameObject_Height / 2.0);

	AnimationState();
	Player_RigidBody->Update(dt);
	Player_SpriteAnimation->Update(dt);
}

void Player::AnimationState()
{
	Player_SpriteAnimation->SetProps("player_idle", 0, 4, 400);

	if (Player_IsWalking) { Player_SpriteAnimation->SetProps("player_walking", 0, 6, 500); }

	if (Player_IsFalling or !Player_IsGrounded) { Player_SpriteAnimation->SetProps("player_jumping", 0, 1, 1); }

	if (Player_IsAttacking) { Player_SpriteAnimation->SetProps("player_stand_hit", 0, 4, PLAYER_ATTACK_TIME / Player_SpriteAnimation->getFrameCount(), true); }

	if (Player_IsWalkAttacking) { Player_SpriteAnimation->SetProps("player_walk_hit", 0, 4, PLAYER_ATTACK_TIME / Player_SpriteAnimation->getFrameCount(), true); }
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
