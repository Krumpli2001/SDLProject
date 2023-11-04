#include "Camera.hpp"

Camera* Camera::Camera_Instance = nullptr;

void Camera::Update(Uint64 dt)
{

	M_WIDTH = Engine::GetInstance()->getMap_W();
	M_HEIGHT = Engine::GetInstance()->getMap_H();
	C_Width = *Engine::GetInstance()->getWindow_W() * Engine::GetInstance()->getScale();
	C_Height = *Engine::GetInstance()->getWindow_H() * Engine::GetInstance()->getScale();

	if (Camera_Target != nullptr)
	{
		//int w = *Engine::GetInstance()->getWindow_W() * Engine::GetInstance()->getScale();
		Camera_ViewBox = { 0, 0, C_Width, C_Height };
		//std::cout << w << "\n";
		//std::cout << Engine::GetInstance()->getScale()<<"\n";
		//std::cout << C_Width << " " << C_Height << "\n";

		Camera_ViewBox.x = Camera_Target->getX() - C_Width / 2.0;
		Camera_ViewBox.y = Camera_Target->getY() - C_Height / 2.0;

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