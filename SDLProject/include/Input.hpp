#pragma once

#include <SDL.h>

enum Axis {HORIZONTAL , VERTICAL};

class Input
{
private:
	Input();
	static Input* Input_Instance;
	const Uint8* Input_KeyStates;
	Uint32 Input_ClickStates{};
	SDL_Event event{};
	
	void KeyUp();
	void KeyDown();
	void ClickUp();
	void ClickDown();
public:
	static inline Input* GetInstance()
	{
		if (Input_Instance == nullptr)
		{
			Input_Instance = new Input();
		}
		return Input_Instance;
	}

	void Listen();
	bool getKeyDown(SDL_Scancode key);
	Uint32 getClickDown();
	int getAxisKey(Axis axis);
	int getElse();
	void interpret(int kod);

	inline SDL_Event getEvent() { return event; }
};

