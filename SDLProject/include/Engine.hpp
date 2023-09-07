#pragma once

#include <SDL.h>

#include "GameMap.hpp"
#include "GameObject.hpp"

#define CREATION_WIDTH 1280
#define CREATION_HEIGHT 720

class Engine
{

private:
	Engine() {};
	static Engine* Engine_Instance;
	bool Engine_IsRunning;
	SDL_Window* Engine_Window;
	SDL_Renderer* Engine_Renderer;
	GameMap* Engine_LevelMap;
	std::vector<GameObject*> Enigine_GameObjects;

public:
	inline static Engine* GetInstance()
	{
		if (Engine_Instance == nullptr)
		{
			Engine_Instance = new Engine();
		}
		return Engine_Instance;
	}

	inline bool GetIsRunning() { return Engine_IsRunning; }
	inline SDL_Renderer* GetRenderer() { return Engine_Renderer; }
	inline GameMap* getLevelMap() { return Engine_LevelMap; }
	inline SDL_Window* getWindow() { return Engine_Window; }

	bool Init();
	bool Clean();
	void Quit();
	void Update();
	void Render();
	void Events();

	//void PopState();
	//void PushState(GameState* current);
	//void ChangeState(GameState* target);

};