#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <unordered_map>

#include "GameMap.hpp"
#include "GameObject.hpp"

#define CREATION_WIDTH 1280
#define CREATION_HEIGHT 720

#define SPAWN 10000

class Engine
{

private:
	Engine() {};

	static Engine* Engine_Instance;
	bool Engine_IsRunning{};
	bool Engine_MenuShowing = true;
	bool Engine_FPSShowing = false;
	SDL_Window* Engine_Window{};
	SDL_Renderer* Engine_Renderer{};
	GameMap* Engine_LevelMap{};
	std::vector<GameObject*> Enigine_GameObjects;
	Mix_Music* Engine_Music{};
	double scale = 1.0;
	double Tscale = 1.0;

	std::unordered_map<std::string, Properties*> Engine_PropsMap;

	Uint64 Engine_SpawnTimer = 10000;
	

	int Window_W{};
	int Window_H{};

	int Map_W{};
	int Map_H{};

	bool Engine_ResetFlag = false;
	int Engine_CollisionLayer = 0;

	void spawn(std::string name);
	void spawnSpecial(std::string name, double x, double y, int hp, int power);


public:
	static inline Engine* GetInstance()
	{
		if (Engine_Instance == nullptr)
		{
			Engine_Instance = new Engine();
		}
		return Engine_Instance;
	}

	inline bool GetIsRunning() { return Engine_IsRunning; }
	inline SDL_Renderer* getRenderer() { return Engine_Renderer; }
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
	inline void setCollisionLayer(int e) { Engine_CollisionLayer = e; }
	inline int getCollisionLayer() { return Engine_CollisionLayer; }
	inline void setScale(double s) { scale = s; }
	inline double getScale() { return scale; }
	inline void setTScale(double s) { Tscale = s; }
	inline double getTScale() { return Tscale; }
	inline void setFPSShowing(bool e) { Engine_FPSShowing = e; }
	inline bool getFPSShowing() { return Engine_FPSShowing; }
	inline void setLevelMap(GameMap* p) { Engine_LevelMap = p; }
	int legmamasabbBlock(int x);

	bool Init();
	bool Clean();
	void Quit();
	void Update();
	void Render();
	void Events();

};