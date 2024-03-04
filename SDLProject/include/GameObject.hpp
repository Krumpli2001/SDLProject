#pragma once
#include <SDL.h>

#include "IObject.hpp"
#include "Transform.hpp"
#include "Point.hpp"
#include "Collider.hpp"
#include "RigidBody.hpp"
#include "SpriteAnimation.hpp"

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

	//visszaadja az adott gameObj középpontját
	inline Point* getOrigin() { return GameObject_Origin; }

	//visszaadja az adott gameObj koordinátáit
	inline Transform* getPosition() { return GameObject_Transform; }

	//beállítja az adott gameObj koordinátáit - azaz teleport
	inline void setPosition(double x, double y) { GameObject_Transform->setX(x); GameObject_Transform->setY(y); }

	//beállítja, hogy az adott gameObj-nek mennyi élete van
	inline void setHP(int newhp) { GameObject_hp = newhp; }

	//visszaadja az adott gameObj életét
	inline int getHP() { return GameObject_hp; }

	//beállítja az adott gameObjeknek a lehetséges maximális életpontját
	inline void setMaxHP(int newhp){ GameObject_MaxHP = newhp; }

	//visszaadja az adott gameObjeknek a lehetséges maximális életpontját
	inline int getMaxHP() { return GameObject_MaxHP; }

	//támadás
	virtual void attacking(Uint64 dt) = 0;

	//beállítja a változót hogy támad-e az adott gameObj
	virtual void setAttacking(bool e) = 0;

	//visszaadja a változót hogy éppen támad-e a gameObj
	virtual bool getAttacking() = 0;
	
	//visszaadja a gameObj Collidert
	virtual Collider* getCollider() = 0;

	//kirajzolja a képernyõre a gameObj-et
	virtual void Draw() = 0;

	//frissíti a gameObj állapotát
	virtual void Update(Uint64 dt) = 0;

	//törli/felszabadítja a gameObj-et
	virtual void Clean() = 0;

	//beállítja az adott gameObj-re vonatkozó gravitáviót
	virtual void setGravity(double G) = 0;

	//visszaadja az adott gameObj-re vonatkozó gravitáviót
	virtual double getAttacktime() = 0;

	//visszaadja, hogy mekkorát sebez az adott gameObj
	virtual int getAttackPower() = 0;

	//beállítja, hogy mekkorát sebez az adott gameObj
	virtual void setAttackPower(int power) = 0;

	//visszaállítja alaphelyzetbe a gameObj-et
	virtual void reset() = 0;

	//visszaadja a gameObj (jelenleg player) inventory-át
	virtual void* getInventory() = 0;

	//visszaadja a gameObj (jelenleg player) inventory-ában kiválasztott helyet
	virtual int getSelectedInventory() = 0;

	//elmenti a gameObj (jelenleg player) inventory-át
	virtual void saveInventory() = 0;

	//beolvassá a gameObj (jelenleg player) inventory-át
	virtual void readInventory() = 0;

	//beállítja az adott gameObj célpontját
	virtual void setTarget(int X, int Y) = 0;
};