#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include "GameMap.hpp"
#include "GameObject.hpp"
#include <unordered_map>

#define CREATION_WIDTH 1280
#define CREATION_HEIGHT 720

#define SPAWN 10000.0

class Engine
{

private:
	Engine() {};
	static Engine* Engine_Instance;
	bool Engine_IsRunning{};
	bool Engine_MenuShowing = false;
	SDL_Window* Engine_Window{};
	SDL_Renderer* Engine_Renderer{};
	GameMap* Engine_LevelMap{};
	std::vector<GameObject*> Enigine_GameObjects;
	Mix_Music* Music{};

	std::unordered_map<std::string, Properties*> Engine_PropsMap;
	std::unordered_map<std::string, GameObject*> Engine_GOMap;

	Uint64 Engine_SpawnTimer = 1000.0;

	int Window_W{};
	int Window_H{};

	int Map_W{};
	int Map_H{};

	bool Engine_ResetFlag = false;

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
	inline int* getWindow_W() { return &Window_W; }
	inline int* getWindow_H() { return &Window_H; }
	inline int getMap_W() { return Map_W; }
	inline int getMap_H() { return Map_H; }
	inline bool getMenuShowing() { return Engine_MenuShowing; }
	inline void setMenuShowing(bool set) { Engine_MenuShowing = set; }
	inline std::vector<GameObject*> getGameObjects() { return Enigine_GameObjects; }
	inline bool getResetFlag() { return Engine_ResetFlag; }
	inline void setResetFlag(bool e) { Engine_ResetFlag = e; }

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