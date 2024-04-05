#pragma once

#include <SDL.h>

#include "GameObject.hpp"

enum playerAniState {
	IsIdle,
	IsWalking,
	IsJumping,
	IsFalling,
	IsAttacking,
	IsWalkingAndAttacking,
};

class Character : public GameObject {
protected:
	std::string Character_Name;
	short Character_AnimationState{};
public:
	inline Character(Properties* props) : GameObject(props) {}
	virtual void AnimationState() = 0;

	inline bool gotHit(std::string texture, Uint64 dt, RigidBody* rigidBody) {
		auto texturemanagerInstance = TextureManager::GetInstance();
		bool r{};
		if (GameObject_kbt > 0) {
			texturemanagerInstance->setTextColor(texturemanagerInstance->getTextureMap()->find(texture)->second.first, "red");
			GameObject_kbt = static_cast<int>(GameObject_kbt - dt);

			rigidBody->ApplyForceY(FEL * GameObject_kb);
			rigidBody->ApplyForceX(Gameobject_kb_direction * GameObject_kb);
			/*Player_IsJumping = true;
			Player_IsGrounded = false;*/
			r = true;
		}
		else {
			texturemanagerInstance->setTextColor(texturemanagerInstance->getTextureMap()->find(texture)->second.first, "white");
			r = false;
		}
		GameObject_kbt = GameObject_kbt < INT_MIN / 2 ? 0 : GameObject_kbt;
		return r;
	}
};