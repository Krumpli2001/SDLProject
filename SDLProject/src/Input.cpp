#include "Camera.hpp"
#include "Engine.hpp"
#include "Input.hpp"
#include "Menu.hpp"
#include "Timer.hpp" // ez kesobb majd valami settinges lesz
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
			case SDL_MOUSEWHEEL:
				if (event.wheel.y > 0) // scroll up
				{
					if (Scroll <= 0) {
						Scroll = 0;
					}
					Scroll++;
				}
				else if (event.wheel.y < 0) // scroll down
				{
					if (Scroll >= 0) {
						Scroll = 0;
					}
					Scroll--;
				}
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
	return Input_ClickStates;
}

int Input::getScroll() {
	if (Scroll == prevScroll) {
		return 0;
	}


	prevScroll = Scroll;
	return Scroll;
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
	if (getKeyDown(SDL_SCANCODE_F2)) { return SDL_SCANCODE_F2; }
	if (getKeyDown(SDL_SCANCODE_F3)) { return SDL_SCANCODE_F3; }

	return 0;
}

void Input::interpret(int kod)
{
	auto timerInstance = Timer::GetInstance();
	constexpr auto press_timer = 200;
	constexpr auto press_timer_setting = 20;
	constexpr auto zoom_increment = 0.004;

	switch (kod)
	{
	case SDL_SCANCODE_1:
		if(timerInstance->pressable(press_timer)){ timerInstance->setFPSLock(!timerInstance->getFPSLock()); }
		break;

	case SDL_SCANCODE_KP_PLUS:
		if (timerInstance->pressable(press_timer_setting)) {
			Engine::GetInstance()->setScale(Engine::GetInstance()->getScale() + zoom_increment);
		}
		break;

	case SDL_SCANCODE_MINUS:
		if (timerInstance->pressable(press_timer_setting)) {
			Engine::GetInstance()->setScale(Engine::GetInstance()->getScale() - zoom_increment);
		}

		break;

	case SDL_SCANCODE_2:
		if (timerInstance->pressable(press_timer)) {
			UI::GetInstance()->setFpsShowing(!UI::GetInstance()->getFpsShowing());
		}
		break;

	case SDL_SCANCODE_F2:
		if (timerInstance->pressable(press_timer_setting)) {
			Engine::GetInstance()->setVolume(Engine::GetInstance()->getVolume() - 1);
		}
		break;

	case SDL_SCANCODE_F3:
		if (timerInstance->pressable(press_timer_setting)) {
			Engine::GetInstance()->setVolume(Engine::GetInstance()->getVolume() + 1);
		}
		break;

	case SDL_SCANCODE_E:
		if (timerInstance->pressable(press_timer)) {
			UI::GetInstance()->setInventoryShowing(!UI::GetInstance()->getInventoryShowing());
		}
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