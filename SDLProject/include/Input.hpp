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
	
	//billenty� fel
	void KeyUp();

	//billenty� le
	void KeyDown();

	//eg�r klikk fel
	void ClickUp();

	//eg�r klikk le
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

	//hallgat�s
	void Listen();

	//adott billenty� le van - e nyomva
	bool getKeyDown(SDL_Scancode key);

	//eg�r klikk �llapota
	Uint32 getClickDown();

	//ir�ny visszat�r�t�se
	int getAxisKey(Axis axis);

	//minden m�s gomb ami nem ir�ny�t�ssal kapcsolatos
	int getElse();

	//az egy�b gombok kezel�se
	void interpret(int kod);

	//eg�r g�rg� kezel�se
	int getScroll();
};

