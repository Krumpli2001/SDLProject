#include "Camera.hpp"

Camera* Camera::Camera_Instance = nullptr;

void Camera::Update(Uint64 dt)
{

	M_WIDTH = Engine::GetInstance()->getMap_W();
	M_HEIGHT = Engine::GetInstance()->getMap_H();

	if (Camera_Target != nullptr)
	{
		Camera_ViewBox = { 0, 0, *Engine::GetInstance()->getWindow_W(), *Engine::GetInstance()->getWindow_H() };


		Camera_ViewBox.x = Camera_Target->getX() - *Engine::GetInstance()->getWindow_W() / 2.0;
		Camera_ViewBox.y = Camera_Target->getY() - *Engine::GetInstance()->getWindow_H() / 2.0;

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