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
	int Engine_CollisionLayer{};
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

	//a main loopnak van, hogy fusson-e m�g a program 
	inline bool GetIsRunning() { return Engine_IsRunning; }

	//renderer pointert ad vissza
	inline SDL_Renderer* getRenderer() { return Engine_Renderer; }

	//a gameMap mutat�j�t adja vissza
	inline GameMap* getLevelMap() { return Engine_LevelMap; }

	//az ablak mutat�j�t adja vissza
	inline SDL_Window* getWindow() { return Engine_Window; }

	//az ablak sz�less�g�t adja vissza
	inline int* getWindow_W() { return &Window_W; }

	//az ablak magass�g�t adja vissza
	inline int* getWindow_H() { return &Window_H; }

	//a palya sz�lesseget adja vissza, pixelekben
	inline int getMap_W() { return Map_W; }

	//a palya magassagat adja vissza, pixelekben
	inline int getMap_H() { return Map_H; }

	//a palya sz�less�g�t al�tja be, pixelekben
	inline void setMap_W(int e) { Map_W = e; }

	//a p�lya magass�g�t �ll�tja be, pixelekben
	inline void setMap_H(int e) { Map_H = e; }

	//visszaadja hogy a menu akt�v-e
	inline bool getMenuShowing() { return Engine_MenuShowing; }

	//be�ll�tja, hogy a menu akt�v-e
	inline void setMenuShowing(bool set) { Engine_MenuShowing = set; }

	//visszaadja a gameObj pointer vektor pointer�t
	inline std::vector<GameObject*>* getGameObjects() { return &Enigine_GameObjects; }

	//visszaadja a props mappot
	inline std::unordered_map<std::string, Properties*>* getPropsMap() { return &Engine_PropsMap; }

	//visszaadja a reset flag-et
	inline bool getResetFlag() { return Engine_ResetFlag; }

	//be�ll�tja a reset flag-et
	inline void setResetFlag(bool e) { Engine_ResetFlag = e; }

	//be�ll�tja a collision vektor index�t 
	inline void setCollisionLayer(int e) { Engine_CollisionLayer = e; }

	//visszaadja a collision layer index�t
	inline int getCollisionLayer() { return Engine_CollisionLayer; }

	//be�ll�tja a zoom skal�rt
	inline void setScale(double s) { scale = s; }

	//visszaadja a zoom skal�rt
	inline double getScale() { return scale; }

	//be�ll�tja, hogy van e akt�v map bet�ltve
	inline void setmapIsLoaded(bool e) { mapIsLoaded = e; }

	//be�ll�tja a levelmap pointert
	inline void setLevelMap(GameMap* p) { Engine_LevelMap = p; }

	//be�ll�tja a collision layer vetor pointer�t
	inline void setCollisionLayerVector(std::vector<std::vector<int>>* p) { Engine_CollisionLayerVector = p; }

	//visszaadja a collision layer vetor pointer�t
	inline std::vector<std::vector<int>>* getCollisionLayerVector() { return Engine_CollisionLayerVector; }

	//be�ll�tja a blokkok m�ret�t
	inline void setTileSize(int i) { TileSize = i; }

	//visszaadja a blokkok m�ret�t
	inline int getTileSize() { return TileSize; }

	//kisz�molja adott x koordin�t�ra a legmagasabb y koordin�t�t
	int legmamasabbBlock(int x);

	//visszaadja hogy adott gameObj spawnolhat-e x y koordin�t�kat
	bool spawnolhat(int x, int* y, int w, int h);

	//be�ll�tja a p�lya nev�t
	inline void setMapName(std::string str) { loaded_map_name = str; }

	//visszaadja a p�lya nev�t
	inline std::string getMapName() { return loaded_map_name; }


	//visszaadja a hanger�t
	inline int getVolume() { return volume; }

	//be�ll�tja a hanger�t
	inline void setVolume(int e) { volume = e; }

	//be�ll�tja a flora layer index�t
	inline void setFloraLayer(int e) { flora_layer = e; }

	//be�ll�tja a background layer index�t
	inline void setBackgroundLayer(int e) { background_layer = e; }

	//visszaadja a flora layer index�t
	inline int getFloraLayer() { return flora_layer; }

	//visszaadja a background layer index�t
	inline int getBackgroundLayer() { return background_layer; }

	//be�ll�tja a flora layer vektor�t
	inline void setFloraLayerVector(std::vector<std::vector<int>>* p) { Engine_FloraLayerVector = p; }

	//be�ll�tja a background layer vektor�t
	inline void setBackgroundLayerVector(std::vector<std::vector<int>>* p) { Engine_BackgroundLayerVector = p; }

	//visszaadja a flora layer vektor�t
	inline std::vector<std::vector<int>>* getFloraLayerVector() { return Engine_FloraLayerVector; }

	//visszaadja a background layer vektor�t
	inline std::vector<std::vector<int>>* getBackgroundLayerVector() { return Engine_BackgroundLayerVector; }

	//setup
	bool Init();
	//mem�ria felszabad�t�sa
	bool Clean();
	//kil�p�s
	void Quit();
	//minden friss�t�se
	//eltelt id� az el�z� frame �ta (delta time)
	void Update();
	//minden ki�r�sa
	void Render();
	//h�tt�r megjelen�t�se
	void drawBG(std::string id, int y);
	//eventek hallgat�sa (mnk, stb.)
	void Events();

	/*spawnol�s f�ggv�ny
	mob neve
	x koord
	y koord
	hp mennyis�ge
	�t�se ereje
	*/
	void spawnSpecial(std::string name, double x, double y, int hp = 100, int power = 10);

	//map ment�se
	void map_save();

};