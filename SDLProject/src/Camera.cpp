#include "Camera.hpp"

Camera* Camera::Camera_Instance = nullptr;

void Camera::Update()
{
	auto engineInstance = Engine::GetInstance();
	scale = engineInstance->getScale();
	M_WIDTH = engineInstance->getMap_W();
	M_HEIGHT = engineInstance->getMap_H();
	C_Width = *engineInstance->getWindow_W();
	C_Height = *engineInstance->getWindow_H();
	C_X = static_cast<int>(Camera_Target->getX() - C_Width / (2.0 * scale));
	C_Y = static_cast<int>(Camera_Target->getY() - C_Height / (2.0 * scale));

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
			Camera_ViewBox.x = static_cast<int>(M_WIDTH - Camera_ViewBox.w * (1.0 / scale));
		}

		if (Camera_ViewBox.y > M_HEIGHT - Camera_ViewBox.h * (1.0 / scale))
		{
			Camera_ViewBox.y = static_cast<int>(M_HEIGHT - Camera_ViewBox.h * (1.0 / scale));
		}

		Camera_Position = Vector2D(Camera_ViewBox.x, Camera_ViewBox.y);

	}
}