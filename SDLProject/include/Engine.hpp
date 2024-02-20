#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <unordered_map>
#include <fstream>

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
	SDL_Window* Engine_Window{};
	SDL_Renderer* Engine_Renderer{};
	GameMap* Engine_LevelMap{};
	std::vector<GameObject*> Enigine_GameObjects;
	Mix_Music* Engine_Music{};
	double scale = 0.5;
	int volume = MIX_MAX_VOLUME;

	std::unordered_map<std::string, Properties*> Engine_PropsMap;

	double Engine_SpawnTimer = SPAWN;
	

	int Window_W{};
	int Window_H{};

	int Map_W{};
	int Map_H{};

	bool Engine_ResetFlag = false;
	int Engine_CollisionLayer = 0;
	int flora_layer{};
	int background_layer{};
	bool mapIsLoaded = false;

	std::vector<std::vector<int>>* Engine_CollisionLayerVector = nullptr;
	std::vector<std::vector<int>>* Engine_FloraLayerVector = nullptr;
	std::vector<std::vector<int>>* Engine_BackgroundLayerVector = nullptr;
	int TileSize{};

	void spawn(std::string name);

	std::string loaded_map_name;

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
	inline void setMap_W(int e) { Map_W = e; }
	inline void setMap_H(int e) { Map_H = e; }
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
	inline void setmapIsLoaded(bool e) { mapIsLoaded = e; }
	inline void setLevelMap(GameMap* p) { Engine_LevelMap = p; }
	inline void setCollisionLayerVector(std::vector<std::vector<int>>* p) { Engine_CollisionLayerVector = p; }
	inline std::vector<std::vector<int>>* getCollisionLayerVector() { return Engine_CollisionLayerVector; }
	inline void setTileSize(int i) { TileSize = i; }
	inline int getTileSize() { return TileSize; }
	int legmamasabbBlock(int x);
	bool spawnolhat(int x, int* y, int w, int h);

	inline void setMapName(std::string str) { loaded_map_name = str; }
	inline std::string getMapName() { return loaded_map_name; }

	inline int getVolume() { return volume; }
	inline void setVolume(int e) { volume = e; }

	inline void setFloraLayer(int e) { flora_layer = e; }
	inline void setBackgroundLayer(int e) { background_layer = e; }
	inline int getFloraLayer() { return flora_layer; }
	inline int getBackgroundLayer() { return background_layer; }

	inline void setFloraLayerVector(std::vector<std::vector<int>>* p) { Engine_FloraLayerVector = p; }
	inline void setBackgroundLayerVector(std::vector<std::vector<int>>* p) { Engine_BackgroundLayerVector = p; }
	inline std::vector<std::vector<int>>* getFloraLayerVector() { return Engine_FloraLayerVector; }
	inline std::vector<std::vector<int>>* getBackgroundLayerVector() { return Engine_BackgroundLayerVector; }


	bool Init();
	bool Clean();
	void Quit();
	void Update();
	void Render();
	void drawBG(std::string id, int y);
	void Events();

	void spawnSpecial(std::string name, double x, double y, int hp = 100, int power = 10);


	void map_save();



};