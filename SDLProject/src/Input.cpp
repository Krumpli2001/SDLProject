#include "Input.hpp"
#include "Engine.hpp"
#include "Camera.hpp"
#include "Timer.hpp" // ez kesobb majd valami settinges lesz
#include "Menu.hpp"

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
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					SDL_GetWindowSizeInPixels(Engine::GetInstance()->getWindow(), Engine::GetInstance()->getWindow_W(), Engine::GetInstance()->getWindow_H());
				}
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

	/*if (Input_KeyStates[key] == 1)
	{
		return true;
	}
	return false;*/
}

Uint32 Input::getClickDown()
{
	Uint32 returner = Input_ClickStates;
	Input_ClickStates = 0;
	return returner;
}


int Input::getElse()
{
	//int i = 0;
	//getKeyDown()
	if (getKeyDown(SDL_SCANCODE_ESCAPE)) { return 1; }
	if (getKeyDown(SDL_SCANCODE_1)) { return 2; }
	if (getKeyDown(SDL_SCANCODE_DOWN)) { return 3; }
	if (getKeyDown(SDL_SCANCODE_UP)) { return 4; }
	if (getKeyDown(SDL_SCANCODE_RETURN)) { return 5; } // ez az enter


	return 0;
}

void Input::interpret(int kod)
{
	int i = 0;
	switch (kod)
	{
	case 1:
		Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing());
		SDL_Delay(150);
		break;
	case 2:
		Timer::GetInstance()->fpslock = !Timer::GetInstance()->fpslock;
		SDL_Delay(150);
		break;
	case 3:
		Menu::GetInstance()->setHighlighted(-1);
		SDL_Delay(150);
		break;
	case 4:
		Menu::GetInstance()->setHighlighted(1);
		SDL_Delay(150);
		break;
	case 5:
		Menu::GetInstance()->setEnter();
	}

}

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