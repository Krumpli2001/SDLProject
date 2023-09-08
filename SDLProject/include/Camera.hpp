#pragma once

#include <SDL.h>

#include "Point.hpp"
#include "Vector2D.hpp"
#include "Engine.hpp"

#define M_WIDTH 7200
#define M_HEIGHT 2400

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

public:
	inline static Camera* GetInstance()
	{
		if (Camera_Instance == nullptr)
		{
			Camera_Instance = new Camera();
		}
		return Camera_Instance;
	}

	inline SDL_Rect* getCamera_ViewDox() { return &Camera_ViewBox; }

	inline SDL_Rect getViewBox() { return Camera_ViewBox; }
	inline Vector2D getPosition() { return Camera_Position; }
	inline void setTarget(Point* target) { Camera_Target = target; }

	void Update(Uint64 dt);

};