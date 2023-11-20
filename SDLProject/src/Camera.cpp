#include "Camera.hpp"

Camera* Camera::Camera_Instance = nullptr;

void Camera::Update(Uint64 dt)
{

	M_WIDTH = Engine::GetInstance()->getMap_W();
	M_HEIGHT = Engine::GetInstance()->getMap_H();
	C_Width = *Engine::GetInstance()->getWindow_W() * Engine::GetInstance()->getScale();
	C_Height = *Engine::GetInstance()->getWindow_H() * Engine::GetInstance()->getScale();
	C_X = Camera_Target->getX() - *Engine::GetInstance()->getWindow_W() / 2.0;
	C_Y = Camera_Target->getY() - *Engine::GetInstance()->getWindow_H() / 2.0;

	SDL_RenderSetScale(Engine::GetInstance()->getRenderer(), Engine::GetInstance()->getScale(), Engine::GetInstance()->getScale());

	if (Camera_Target != nullptr)
	{
		Camera_ViewBox = { C_X, C_Y, C_Width, C_Height };


		if (Camera_ViewBox.x < 0)
		{
			Camera_ViewBox.x = 0;
		}

		if (Camera_ViewBox.y < 0)
		{
			Camera_ViewBox.y = 0;
		}

		if (Camera_ViewBox.x > (M_WIDTH - Camera_ViewBox.w))
		{
			Camera_ViewBox.x = (M_WIDTH - Camera_ViewBox.w);
		}

		if (Camera_ViewBox.y > (M_HEIGHT - Camera_ViewBox.h))
		{
			Camera_ViewBox.y = (M_HEIGHT - Camera_ViewBox.h);
		}

		Camera_Position = Vector2D(Camera_ViewBox.x, Camera_ViewBox.y);

	}
}