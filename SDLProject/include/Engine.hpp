#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <unordered_map>

#include "GameMap.hpp"
#include "GameObject.hpp"
#include "Timer.hpp"

#define CREATION_WIDTH 1280
#define CREATION_HEIGHT 720

#define SPAWN 1000

class Engine
{

private:
	Engine() {};

	static Engine* Engine_Instance;
	bool Engine_IsRunning{};
	bool Engine_MenuShowing = true;
	//bool Engine_FPSShowing = false;
	SDL_Window* Engine_Window{};
	SDL_Renderer* Engine_Renderer{};
	GameMap* Engine_LevelMap{};
	std::vector<GameObject*> Enigine_GameObjects;
	Mix_Music* Engine_Music{};
	double scale = 0.5;
	double Tscale = 1.0;

	std::unordered_map<std::string, Properties*> Engine_PropsMap;

	double Engine_SpawnTimer = SPAWN;
	

	int Window_W{};
	int Window_H{};

	int Map_W{};
	int Map_H{};

	bool Engine_ResetFlag = false;
	int Engine_CollisionLayer = 0;
	bool mapIsLoaded = false;

	std::vector<std::vector<int>>* Engine_CollisionLayerVector = nullptr;
	int TileSize;

	void spawn(std::string name);

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
	inline std::vector<GameObject*>* getGameObjects() { return &Enigine_GameObjects; }
	inline std::unordered_map<std::string, Properties*>* getPropsMap() { return &Engine_PropsMap; }
	inline bool getResetFlag() { return Engine_ResetFlag; }
	inline void setResetFlag(bool e) { Engine_ResetFlag = e; }
	inline void setCollisionLayer(int e) { Engine_CollisionLayer = e; }
	inline int getCollisionLayer() { return Engine_CollisionLayer; }
	inline void setScale(double s) { scale = s; }
	inline double getScale() { return scale; }
	inline void setTScale(double s) { Tscale = s; }
	inline double getTScale() { return Tscale; }
	inline void setmapIsLoaded(bool e) { mapIsLoaded = e; }
	inline void setLevelMap(GameMap* p) { Engine_LevelMap = p; }
	inline void setCollisionLayerVector(std::vector<std::vector<int>>* p) { Engine_CollisionLayerVector = p; }
	//inline std::vector<std::vector<int>>* getColli
	inline void setTileSize(int i) { TileSize = i; }
	inline int getTileSize() { return TileSize; }
	int legmamasabbBlock(int x);
	bool spawnolhat(int x, int* y, int w, int h);

	bool Init();
	bool Clean();
	void Quit();
	void Update();
	void Render();
	void Events();

	void spawnSpecial(std::string name, double x, double y, int hp, int power);


};