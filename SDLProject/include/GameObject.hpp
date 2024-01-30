#pragma once
#include <SDL.h>

#include "IObject.hpp"
#include "Transform.hpp"
#include "Point.hpp"
#include "Collider.hpp"
#include "RigidBody.hpp"
#include "SpriteAnimation.hpp"
//#include "ObjectFactory.hpp"

#define PLAYER_ATTACK_TIME 300.0

class Properties {
public:
	int Properies_hp;
	std::string Properties_TextureID;
	int Properties_Width;
	int Properties_Height;
	double Properties_X;
	double Properties_Y;
	SDL_RendererFlip Properties_Flip;

	inline Properties(std::string textureID, int hp, int width, int height, double x, double y, SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		Properties_TextureID = textureID;
		Properies_hp = hp;
		Properties_Width = width;
		Properties_Height = height;
		Properties_X = x;
		Properties_Y = y;
		Properties_Flip = flip;
	}
};

class GameObject : public IObject {
private:
protected:
	int GameObject_hp;
	int GameObject_MaxHP;
	Transform* GameObject_Transform;
	int GameObject_Width;
	int GameObject_Height;
	std::string GameObject_TextureID;
	SDL_RendererFlip GameObject_Flip;
	Point* GameObject_Origin;

	//int w{};
	//int h{};
public:
	inline GameObject(Properties* props)
	{
		GameObject_hp = props->Properies_hp;
		GameObject_MaxHP = props->Properies_hp;
		GameObject_TextureID = props->Properties_TextureID;
		GameObject_Width = props->Properties_Width;
		GameObject_Height = props->Properties_Height;
		GameObject_Flip = props->Properties_Flip;
		GameObject_Transform = new Transform(props->Properties_X, props->Properties_Y);
		GameObject_Origin = new Point(props->Properties_X + props->Properties_Width / 2, props->Properties_Y + props->Properties_Height / 2);
	}

	inline Point* getOrigin() { return GameObject_Origin; }
	inline Transform* getPosition() { return GameObject_Transform; }
	inline void setPosition(double x, double y)
	{
		GameObject_Transform->setX(x); GameObject_Transform->setY(y);
	}
	inline void setHP(int newhp) { GameObject_hp = newhp; }
	inline int getHP() { return GameObject_hp; }
	inline void setMaxHP(int newhp){ GameObject_MaxHP = newhp; }
	inline int getMaxHP() { return GameObject_MaxHP; }

	virtual void attacking(Uint64 dt) = 0;
	virtual void setAttacking(bool e) = 0;
	virtual bool isAttacking() = 0;
	
	virtual Collider* getCollider() = 0;
	virtual void Draw() = 0;
	virtual void Update(Uint64 dt) = 0;
	virtual void Clean() = 0;
	virtual void setGravity(double G) = 0;
	virtual double getAttacktime() = 0;
	virtual int getAttackPower() = 0;
	virtual void setAttackPower(int power) = 0;
	virtual void reset() = 0;
	virtual void* getInventory() = 0;
	virtual int getSelectedInventory() = 0;
};