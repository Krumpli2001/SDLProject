#include <SDL.h>

#include "Player.hpp"
#include "ObjectFactory.hpp"
#include "Input.hpp"

static Registrar < Player > registrar("PLAYER");

Player::Player(Properties* props) : Character(props)
{

	Player_IsWalking = false;
	Player_IsJumping = false;
	Player_IsFalling = false;
	Player_IsGrounded = false;
	Player_IsAttacking = false;
	Player_IsWalkAttacking = false;

	Player_JumpTime = JUMP_TIME;
	//Player_JumpForce = JUMP_FORCE;
	Player_AttackTime = ATTACK_TIME;

	Player_Collider = new Collider();
	Player_Collider->setBuffer(0, 0, 0, 0);

	Player_RigidBody = new RigidBody();
	Player_RigidBody->setRigidBody_Gravity(GRAVITY);

	Player_SpriteAnimation = new SpriteAnimation();
	Player_SpriteAnimation->SetProps(GameObject_TextureID, 0, 6, 100);
}

void Player::Draw()
{
	Player_SpriteAnimation->Draw(GameObject_Transform->getX(), GameObject_Transform->getY(), GameObject_Width, GameObject_Height, GameObject_Flip, 1.0, 1.0);
}

void Player::Update(Uint64 dt)
{
	Player_IsWalking = false;
	Player_RigidBody->SetForceToZero();
	//std::cout << dt<< "\t"<< Player_JumpTime<<"\n";

	//fut jobbra
	if (Input::GetInstance()->getAxisKey(HORIZONTAL) == JOBBRA and !Player_IsAttacking)
	{
		Player_RigidBody->ApplyForceX(JOBBRA * RUN_FORCE * dt);
		GameObject_Flip = SDL_FLIP_NONE;
		Player_IsWalking = true;
	}

	//fut balra
	if (Input::GetInstance()->getAxisKey(HORIZONTAL) == BALRA and !Player_IsAttacking)
	{
		Player_RigidBody->ApplyForceX(BALRA * RUN_FORCE * dt);
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
		Player_RigidBody->ApplyForceX(JOBBRA * RUN_FORCE * dt);
		GameObject_Flip = SDL_FLIP_NONE;
	}

	//balra fut / ut
	if (Input::GetInstance()->getAxisKey(HORIZONTAL) == BALRA and Player_IsAttacking)
	{
		Player_IsWalkAttacking = true;
		Player_RigidBody->ApplyForceX(BALRA * RUN_FORCE * dt);
		GameObject_Flip = SDL_FLIP_HORIZONTAL;
	}

	//jump
	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_SPACE) and Player_IsGrounded)
	{
		Player_IsJumping = true;
		Player_IsGrounded = false;
		Player_RigidBody->ApplyForceY(FEL * (JUMP_FORCE));
	}

	if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_SPACE) and Player_IsJumping and Player_JumpTime > 0 and Player_JumpTime <=200 )
	{
		Player_JumpTime = Player_JumpTime - dt;
		Player_RigidBody->ApplyForceY(FEL * (JUMP_FORCE));
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
		Player_AttackTime = ATTACK_TIME;
	}

	//collision

	Player_LastSafePosition.setX(GameObject_Transform->getX());
	GameObject_Transform->setX(GameObject_Transform->getX() + Player_RigidBody->getRigidBody_Position().getX());
	Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 190, 240);

	if (CollisionHandler::GetInstance()->MapCollision(Player_Collider->getBox()))
	{
		GameObject_Transform->setX(Player_LastSafePosition.getX());
	}

	Player_LastSafePosition.setY(GameObject_Transform->getY());
	//levitalas miatt van itt
	int y = Player_LastSafePosition.getY();
	if ((y % CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize()) >= (CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize() - 10)) {
		Player_LastSafePosition.setY(GameObject_Transform->getY() + ((CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize() -1)) - (y % CollisionHandler::GetInstance()->CollisionHandler_CollisionLayer->getTileSize()));
	}
	GameObject_Transform->setY(GameObject_Transform->getY() + Player_RigidBody->getRigidBody_Position().getY());
	Player_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 190, 240);

	if (CollisionHandler::GetInstance()->MapCollision(Player_Collider->getBox()))
	{
			Player_IsGrounded = true;
			Player_JumpTime = JUMP_TIME;
			GameObject_Transform->setY(Player_LastSafePosition.getY());
	}
	else
	{
		Player_IsGrounded = false;
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

	if (Player_IsJumping or Player_IsFalling) { Player_SpriteAnimation->SetProps("player_jumping", 0, 1, 1); }

	if (Player_IsAttacking) { Player_SpriteAnimation->SetProps("player_stand_hit", 0, 4, ATTACK_TIME / Player_SpriteAnimation->getFrameCount(), true); }

	if (Player_IsWalkAttacking) { Player_SpriteAnimation->SetProps("player_walk_hit", 0, 4, ATTACK_TIME / Player_SpriteAnimation->getFrameCount(), true); }
}

void Player::Clean()
{
	TextureManager::GetInstance()->Drop(GameObject_TextureID);
}