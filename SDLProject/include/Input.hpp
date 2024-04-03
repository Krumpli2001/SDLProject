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
	int Scroll{};
	int prevScroll{};
	
	//billentyû fel
	void KeyUp();

	//billentyû le
	void KeyDown();

	//egér klikk fel
	void ClickUp();

	//egér klikk le
	void ClickDown();

public:
	static inline Input* GetInstance(bool del = false)
	{
		if (del) {
			if (Input_Instance) {
				delete Input_Instance;
			}
			Input_Instance = nullptr;
			return nullptr;
		}
		if (Input_Instance == nullptr)
		{
			Input_Instance = new Input();
		}
		return Input_Instance;
	}

	//hallgatás
	void Listen();

	//adott billentyû le van - e nyomva
	bool getKeyDown(SDL_Scancode key);

	//egér klikk állapota
	Uint32 getClickDown();

	//irány visszatérítése
	int getAxisKey(Axis axis);

	//minden más gomb ami nem irányítással kapcsolatos
	int getElse();

	//az egyéb gombok kezelése
	void interpret(int kod);

	//egér görgõ kezelése
	int getScroll();
};

