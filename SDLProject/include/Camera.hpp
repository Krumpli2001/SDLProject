#pragma once

#include <SDL.h>

#include "Point.hpp"
#include "Vector2D.hpp"
#include "Engine.hpp"


class Camera
{
private:
	Camera() {
		SDL_GetWindowSizeInPixels(Engine::GetInstance()->getWindow(), Engine::GetInstance()->getWindow_W(), Engine::GetInstance()->getWindow_H());
		Camera_ViewBox = { 0, 0, *Engine::GetInstance()->getWindow_W(), *Engine::GetInstance()->getWindow_H() };
	}

	static Camera* Camera_Instance;
	Point* Camera_Target{};
	Vector2D Camera_Position{};
	SDL_Rect Camera_ViewBox{};

	int M_WIDTH{};
	int M_HEIGHT{};

	int C_Width{};
	int	C_Height{};
	int C_X{};
	int C_Y{};

	double scale{};

public:
	static inline Camera* GetInstance()
	{
		if (Camera_Instance == nullptr)
		{
			Camera_Instance = new Camera();
		}
		return Camera_Instance;
	}

	//visszaadja a kamera "téglalapját" a pályához viszonyítva
	//tehát az x, y koordináta a pályán levõ koordinátákat jelképezik
	//a w és h pedig a kamera méretét
	inline SDL_Rect* getCamera_ViewBox() { return &Camera_ViewBox; }

	//csak a kamera viewbox x, y koordinátáit adja vissza
	inline Vector2D getPosition() { return Camera_Position; }

	//beállítja, hogy a kamera mit kövessen (általában ez egy gameObj)
	inline void setTarget(Point* target) { Camera_Target = target; }

	//kamera adatainak frissülése (minden frame-ben)
	void Update();

};