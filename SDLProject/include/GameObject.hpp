#pragma once
#include <SDL.h>

#include "IObject.hpp"
#include "Transform.hpp"
#include "Point.hpp"

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
	int hp;
	Transform* GameObject_Transform;
	int GameObject_Width;
	int GameObject_Height;
	std::string GameObject_TextureID;
	SDL_RendererFlip GameObject_Flip;
	Point* GameObject_Origin;
public:
	inline GameObject(Properties* props)
	{
		GameObject_TextureID = props->Properties_TextureID;
		GameObject_Width = props->Properties_Width;
		GameObject_Height = props->Properties_Height;
		GameObject_Flip = props->Properties_Flip;
		GameObject_Transform = new Transform(props->Properties_X, props->Properties_Y);
		GameObject_Origin = new Point(props->Properties_X + props->Properties_Width / 2, props->Properties_Y + props->Properties_Height / 2);
	}

	inline Point* getOrigin() { return GameObject_Origin; }

	inline int getHP() { return hp; }

	virtual void Draw() = 0;
	virtual void Update(Uint64 dt) = 0;
	virtual void Clean() = 0;
	virtual void setGravity(double G) = 0;
};