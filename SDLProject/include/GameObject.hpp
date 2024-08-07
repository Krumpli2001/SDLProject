#pragma once
#include <SDL.h>

#include "Collider.hpp"
//#include "IObject.hpp"
#include "Point.hpp"
#include "RigidBody.hpp"
#include "SpriteAnimation.hpp"
#include "Transform.hpp"


class Properties {
public:
	int Properies_hp;
	SDL_RendererFlip Properties_Flip;
	std::string Properties_TextureID;
	int Properties_Width;
	int Properties_Height;
	double Properties_X;
	double Properties_Y;

	inline Properties(const std::string& textureID, int hp, int width, int height, double x, double y, SDL_RendererFlip flip = SDL_FLIP_NONE)
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

class GameObject/* : public IObject */{
private:
protected:
	int GameObject_hp;
	int GameObject_MaxHP;
	Transform GameObject_Transform;
	int GameObject_Width;
	int GameObject_Height;
	std::string GameObject_TextureID;
	SDL_RendererFlip GameObject_Flip;
	Point GameObject_Origin;
	Dimenziok GameObject_Dimenziok{};

	int GameObject_kb{};
	int GameObject_kbt{};
	int Gameobject_kb_direction{};

public:
	inline GameObject(Properties* props)
	{
		GameObject_hp = props->Properies_hp;
		GameObject_MaxHP = props->Properies_hp;
		GameObject_TextureID = props->Properties_TextureID;
		GameObject_Width = props->Properties_Width;
		GameObject_Height = props->Properties_Height;
		GameObject_Flip = props->Properties_Flip;
		GameObject_Transform = Transform(props->Properties_X, props->Properties_Y);
		GameObject_Origin = Point(props->Properties_X + props->Properties_Width / 2, props->Properties_Y + props->Properties_Height / 2);
	}

	/*inline ~GameObject() {
		delete GameObject_Transform;
		delete GameObject_Origin;
	}*/

	//visszaadja az adott gameObj k�z�ppontj�t
	inline Point* getOrigin() { return &GameObject_Origin; }

	//visszaadja az adott gameObj koordin�t�it
	inline Transform* getPosition() { return &GameObject_Transform; }

	//be�ll�tja az adott gameObj koordin�t�it - azaz teleport
	inline void setPosition(double x, double y) { GameObject_Transform.setX(x); GameObject_Transform.setY(y); }

	//be�ll�tja, hogy az adott gameObj-nek mennyi �lete van
	inline void setHP(int newhp) { GameObject_hp = newhp; }

	//visszaadja az adott gameObj �let�t
	inline int getHP() const { return GameObject_hp; }

	//be�ll�tja az adott gameObjeknek a lehets�ges maxim�lis �letpontj�t
	inline void setMaxHP(int newhp){ GameObject_MaxHP = newhp; }

	//visszaadja az adott gameObjeknek a lehets�ges maxim�lis �letpontj�t
	inline int getMaxHP() const { return GameObject_MaxHP; }

	//t�mad�s
	virtual bool attacking(Uint64 dt) = 0;

	//be�ll�tja a v�ltoz�t hogy t�mad-e az adott gameObj
	virtual void setAttacking(bool e) = 0;

	//visszaadja a v�ltoz�t hogy �ppen t�mad-e a gameObj
	virtual bool getAttacking() = 0;
	
	//visszaadja a gameObj Collidert
	virtual Collider* getCollider() = 0;

	//kirajzolja a k�perny�re a gameObj-et
	virtual void Draw() = 0;

	//friss�ti a gameObj �llapot�t
	virtual void Update(Uint64 dt) = 0;

	//t�rli/felszabad�tja a gameObj-et
	virtual void Clean() = 0;

	//be�ll�tja az adott gameObj-re vonatkoz� gravit�vi�t
	virtual void setGravity(double G) = 0;

	//visszaadja az adott gameObj-re vonatkoz� gravit�vi�t
	virtual double getAttacktime() = 0;

	//visszaadja, hogy mekkor�t sebez az adott gameObj
	virtual int getAttackPower() = 0;

	//be�ll�tja, hogy mekkor�t sebez az adott gameObj
	virtual void setAttackPower(int power) = 0;

	//vissza�ll�tja alaphelyzetbe a gameObj-et
	virtual void reset() = 0;

	//visszaadja a gameObj (jelenleg player) inventory-�t
	virtual void* getInventory() = 0;

	//visszaadja a gameObj (jelenleg player) inventory-�ban kiv�lasztott helyet
	virtual int getSelectedInventory() = 0;

	//elmenti a gameObj (jelenleg player) inventory-�t
	virtual void saveInventory() = 0;

	//beolvass� a gameObj (jelenleg player) inventory-�t
	virtual void readInventory() = 0;

	//be�ll�tja az adott gameObj c�lpontj�t
	virtual void setTarget(int X, int Y) = 0;

	//a sebz�d�s efekt
	inline void TookDMG(int irany, int kb = 2, int kbt = 50) {
		GameObject_kbt = kbt;
		GameObject_kb = kb;
		Gameobject_kb_direction = irany;
	}
};