#include "Camera.hpp"

Camera* Camera::Camera_Instance = nullptr;

void Camera::Update(Uint64 dt)
{
	if (Camera_Target != nullptr)
	{

		Camera_ViewBox.x = Camera_Target->getX() - Camera_W / 2.0;
		Camera_ViewBox.y = Camera_Target->getY() - Camera_H / 2.0;

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