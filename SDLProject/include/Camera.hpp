#pragma once

#include <SDL.h>

#include "Engine.hpp"
#include "Point.hpp"
#include "Vector2D.hpp"


class Camera
{
private:
	Camera() {
		auto engineInstance = Engine::GetInstance();
		SDL_GetWindowSizeInPixels(engineInstance->getWindow(), engineInstance->getWindow_W(), engineInstance->getWindow_H());
		constexpr int kezdoX = 0; constexpr int kezdoY = 0;
		Camera_ViewBox = { kezdoX, kezdoY, *engineInstance->getWindow_W(), *engineInstance->getWindow_H() };
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

	//visszaadja a kamera "t�glalapj�t" a p�ly�hoz viszony�tva
	//teh�t az x, y koordin�ta a p�ly�n lev� koordin�t�kat jelk�pezik
	//a w �s h pedig a kamera m�ret�t
	inline SDL_Rect* getCamera_ViewBox() { return &Camera_ViewBox; }

	//csak a kamera viewbox x, y koordin�t�it adja vissza
	inline Vector2D getPosition() const { return Camera_Position; }

	//be�ll�tja, hogy a kamera mit k�vessen (�ltal�ban ez egy gameObj)
	inline void setTarget(Point* target) { Camera_Target = target; }

	//kamera adatainak friss�l�se (minden frame-ben)
	void Update();

};