#include "Input.hpp"
#include "Engine.hpp"
#include "Camera.hpp"
#include "Timer.hpp" // ez kesobb majd valami settinges lesz
#include "Menu.hpp"
#include "UI.hpp"

Input* Input::Input_Instance = nullptr;

Input::Input()
{
	Input_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyUp()
{
	Input_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{
	Input_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::ClickUp()
{
	Input_ClickStates = SDL_GetMouseState(nullptr, nullptr);
}

void Input::ClickDown()
{
	Input_ClickStates = SDL_GetMouseState(nullptr, nullptr);
}

void Input::Listen()
{

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_WINDOWEVENT:
				switch(event.window.event)
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						SDL_GetWindowSizeInPixels(Engine::GetInstance()->getWindow(), Engine::GetInstance()->getWindow_W(), Engine::GetInstance()->getWindow_H());
						break;
				break;
			case SDL_QUIT:
				Engine::GetInstance()->Quit();
				break;
			case SDL_KEYDOWN:
				KeyDown();
				break;
			case SDL_KEYUP:
				KeyUp();
				break;
			case SDL_MOUSEBUTTONDOWN:
				ClickDown();
				break;
			case SDL_MOUSEBUTTONUP:
				ClickUp();
				break;
		}
	}
}

bool Input::getKeyDown(SDL_Scancode key)
{
	return (Input_KeyStates[key] == 1);
}

Uint32 Input::getClickDown()
{
	//Uint32 returner = Input_ClickStates;
	////Input_ClickStates = 0;
	//return returner;
	return Input_ClickStates;
}


int Input::getElse()
{
	if (getKeyDown(SDL_SCANCODE_ESCAPE)) { SDL_ResetKeyboard();  return SDL_SCANCODE_ESCAPE; }
	if (getKeyDown(SDL_SCANCODE_1)) { return SDL_SCANCODE_1; }
	if (getKeyDown(SDL_SCANCODE_DOWN) /* or getKeyDown(SDL_SCANCODE_S)*/) { return SDL_SCANCODE_DOWN; }
	if (getKeyDown(SDL_SCANCODE_UP) /* or getKeyDown(SDL_SCANCODE_W)*/) { return SDL_SCANCODE_UP; }
	if (getKeyDown(SDL_SCANCODE_RETURN)) { return SDL_SCANCODE_RETURN; }
	//fps szamlalo megjelenitese
	if (getKeyDown(SDL_SCANCODE_2)) { return SDL_SCANCODE_2; }
	//ez a 2 a kamerahoz megy
	if (getKeyDown(SDL_SCANCODE_LSHIFT) and getKeyDown(SDL_SCANCODE_3)) { return SDL_SCANCODE_KP_PLUS; }
	if (getKeyDown(SDL_SCANCODE_LSHIFT) and getKeyDown(SDL_SCANCODE_4)) { return SDL_SCANCODE_MINUS; }
	//ez a 2 a texturakhoz
	if (getKeyDown(SDL_SCANCODE_3)) { return SDL_SCANCODE_3; }
	if (getKeyDown(SDL_SCANCODE_4)) { return SDL_SCANCODE_4; }
	//inventory mutatas
	if (getKeyDown(SDL_SCANCODE_E)) { return SDL_SCANCODE_E; }
	return 0;
}

void Input::interpret(int kod)
{
	switch (kod)
	{
	case SDL_SCANCODE_1:
		if(Timer::GetInstance()->pressable(200)){ Timer::GetInstance()->setFPSLock(!Timer::GetInstance()->getFPSLock()); }
		break;

	case SDL_SCANCODE_KP_PLUS:
		if (Timer::GetInstance()->pressable(200)) {
			Engine::GetInstance()->setScale(Engine::GetInstance()->getScale() + 0.01); 
		}
		break;

	case SDL_SCANCODE_MINUS:
		if (Timer::GetInstance()->pressable(200)) {
			Engine::GetInstance()->setScale(Engine::GetInstance()->getScale() - 0.01);
		}

		break;

	case SDL_SCANCODE_2:
		if (Timer::GetInstance()->pressable(200)) {
			UI::GetInstance()->setFpsShowing(!UI::GetInstance()->getFpsShowing());
		}
		break;

	case SDL_SCANCODE_3:
		if (Timer::GetInstance()->pressable(200)) {
			Engine::GetInstance()->setTScale(Engine::GetInstance()->getTScale() + 0.1);
		}
		break;

	case SDL_SCANCODE_4:
		if (Timer::GetInstance()->pressable(200)) {
			Engine::GetInstance()->setTScale(Engine::GetInstance()->getTScale() - 0.1);
		}
		break;

	case SDL_SCANCODE_E:
		if (Timer::GetInstance()->pressable(200)) {
			UI::GetInstance()->setInventoryShowing(!UI::GetInstance()->getInventoryShowing());
		}
	}
}

//dEpriCateD
//void Input::interpret(int kod)
//{
//	int i = 0;
//	switch (kod)
//	{
//	case 1:
//		Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing());
//		SDL_Delay(150);
//		break;
//	case 2:
//		Timer::GetInstance()->fpslock = !Timer::GetInstance()->fpslock;
//		SDL_Delay(150);
//		break;
//	case 3:
//		Menu::GetInstance()->setHighlighted(-1);
//		SDL_Delay(150);
//		break;
//	case 4:
//		Menu::GetInstance()->setHighlighted(1);
//		SDL_Delay(150);
//		break;
//	case 5:
//		Menu::GetInstance()->setEnter();
//		SDL_Delay(150);
//		break;
//	}
//
//}

int Input::getAxisKey(Axis axis)
{
	switch (axis)
	{
	case HORIZONTAL:
		if (getKeyDown(SDL_SCANCODE_D) or getKeyDown(SDL_SCANCODE_RIGHT)) { return 1; }
		if (getKeyDown(SDL_SCANCODE_A) or getKeyDown(SDL_SCANCODE_LEFT)) { return -1; }
		break;

	case VERTICAL:
		if (getKeyDown(SDL_SCANCODE_W) or getKeyDown(SDL_SCANCODE_UP)) { return 1; }
		if (getKeyDown(SDL_SCANCODE_S) or getKeyDown(SDL_SCANCODE_DOWN)) { return -1; }
		break;

	default:
		return 0;
	}
	return 0;

}