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

	//a main loopnak van, hogy fusson-e még a program 
	inline bool GetIsRunning() { return Engine_IsRunning; }

	//renderer pointert ad vissza
	inline SDL_Renderer* getRenderer() { return Engine_Renderer; }

	//a gameMap mutatóját adja vissza
	inline GameMap* getLevelMap() { return Engine_LevelMap; }

	//az ablak mutatóját adja vissza
	inline SDL_Window* getWindow() { return Engine_Window; }

	//az ablak szélességét adja vissza
	inline int* getWindow_W() { return &Window_W; }

	//az ablak magasságát adja vissza
	inline int* getWindow_H() { return &Window_H; }

	//a palya szélesseget adja vissza, pixelekben
	inline int getMap_W() { return Map_W; }

	//a palya magassagat adja vissza, pixelekben
	inline int getMap_H() { return Map_H; }

	//a palya szélességét alítja be, pixelekben
	inline void setMap_W(int e) { Map_W = e; }

	//a pálya magasságát állítja be, pixelekben
	inline void setMap_H(int e) { Map_H = e; }

	//visszaadja hogy a menu aktív-e
	inline bool getMenuShowing() { return Engine_MenuShowing; }

	//beállítja, hogy a menu aktív-e
	inline void setMenuShowing(bool set) { Engine_MenuShowing = set; }

	//visszaadja a gameObj pointer vektor pointerét
	inline std::vector<GameObject*>* getGameObjects() { return &Enigine_GameObjects; }

	//visszaadja a props mappot
	inline std::unordered_map<std::string, Properties*>* getPropsMap() { return &Engine_PropsMap; }

	//visszaadja a reset flag-et
	inline bool getResetFlag() { return Engine_ResetFlag; }

	//beállítja a reset flag-et
	inline void setResetFlag(bool e) { Engine_ResetFlag = e; }

	//beállítja a collision vektor indexét 
	inline void setCollisionLayer(int e) { Engine_CollisionLayer = e; }

	//visszaadja a collision layer indexét
	inline int getCollisionLayer() { return Engine_CollisionLayer; }

	//beállítja a zoom skalárt
	inline void setScale(double s) { scale = s; }

	//visszaadja a zoom skalárt
	inline double getScale() { return scale; }

	//beállítja, hogy van e aktív map betöltve
	inline void setmapIsLoaded(bool e) { mapIsLoaded = e; }

	//beállítja a levelmap pointert
	inline void setLevelMap(GameMap* p) { Engine_LevelMap = p; }

	//beállítja a collision layer vetor pointerét
	inline void setCollisionLayerVector(std::vector<std::vector<int>>* p) { Engine_CollisionLayerVector = p; }

	//visszaadja a collision layer vetor pointerét
	inline std::vector<std::vector<int>>* getCollisionLayerVector() { return Engine_CollisionLayerVector; }

	//beállítja a blokkok méretét
	inline void setTileSize(int i) { TileSize = i; }

	//visszaadja a blokkok méretét
	inline int getTileSize() { return TileSize; }

	//kiszámolja adott x koordinátára a legmagasabb y koordinátát
	int legmamasabbBlock(int x);

	//visszaadja hogy adott gameObj spawnolhat-e x y koordinátákat
	bool spawnolhat(int x, int* y, int w, int h);

	//beállítja a pálya nevét
	inline void setMapName(std::string str) { loaded_map_name = str; }

	//visszaadja a pálya nevét
	inline std::string getMapName() { return loaded_map_name; }


	//visszaadja a hangerõt
	inline int getVolume() { return volume; }

	//beállítja a hangerõt
	inline void setVolume(int e) { volume = e; }

	//beállítja a flora layer indexét
	inline void setFloraLayer(int e) { flora_layer = e; }

	//beállítja a background layer indexét
	inline void setBackgroundLayer(int e) { background_layer = e; }

	//visszaadja a flora layer indexét
	inline int getFloraLayer() { return flora_layer; }

	//visszaadja a background layer indexét
	inline int getBackgroundLayer() { return background_layer; }

	//beállítja a flora layer vektorát
	inline void setFloraLayerVector(std::vector<std::vector<int>>* p) { Engine_FloraLayerVector = p; }

	//beállítja a background layer vektorát
	inline void setBackgroundLayerVector(std::vector<std::vector<int>>* p) { Engine_BackgroundLayerVector = p; }

	//visszaadja a flora layer vektorát
	inline std::vector<std::vector<int>>* getFloraLayerVector() { return Engine_FloraLayerVector; }

	//visszaadja a background layer vektorát
	inline std::vector<std::vector<int>>* getBackgroundLayerVector() { return Engine_BackgroundLayerVector; }

	//setup
	bool Init();
	//memória felszabadítása
	bool Clean();
	//kilépés
	void Quit();
	//minden frissítése
	//eltelt idõ az elõzõ frame óta (delta time)
	void Update();
	//minden kiírása
	void Render();
	//háttér megjelenítése
	void drawBG(std::string id, int y);
	//eventek hallgatása (mnk, stb.)
	void Events();

	/*spawnolás függvény
	mob neve
	x koord
	y koord
	hp mennyisége
	ütése ereje
	*/
	void spawnSpecial(std::string name, double x, double y, int hp = 100, int power = 10);

	//map mentése
	void map_save();

};