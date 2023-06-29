#include "Input.hpp"
#include "Engine.hpp"

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
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
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

}
