#include "Camera.hpp"

Camera* Camera::Camera_Instance = nullptr;

void Camera::Update(Uint64 dt)
{
	scale = Engine::GetInstance()->getScale();
	M_WIDTH = Engine::GetInstance()->getMap_W();
	M_HEIGHT = Engine::GetInstance()->getMap_H();
	C_Width = *Engine::GetInstance()->getWindow_W();/* * Engine::GetInstance()->getScale();*/
	C_Height = *Engine::GetInstance()->getWindow_H();/* *Engine::GetInstance()->getScale();*/
	C_X = Camera_Target->getX() - C_Width / (2.0 * scale);
	C_Y = Camera_Target->getY() - C_Height / (2.0 * scale);

	SDL_RenderSetScale(Engine::GetInstance()->getRenderer(), scale, scale);

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

		if (Camera_ViewBox.x > M_WIDTH - Camera_ViewBox.w * (1.0 / scale))
		{
			Camera_ViewBox.x = M_WIDTH - Camera_ViewBox.w * (1.0 / scale);
		}

		if (Camera_ViewBox.y > M_HEIGHT - Camera_ViewBox.h * (1.0 / scale))
		{
			Camera_ViewBox.y = M_HEIGHT - Camera_ViewBox.h * (1.0 / scale);
		}

		Camera_Position = Vector2D(Camera_ViewBox.x, Camera_ViewBox.y);

	}
	//std::cout << Camera_ViewBox.x << "\t" << Camera_ViewBox.y << "\n";
}