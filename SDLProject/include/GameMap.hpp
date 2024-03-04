#pragma once

#include <vector>

#include "Layer.hpp"

class GameMap {
private:
	//friend class MapParser;
	std::vector<Layer*> GameMap_MapLayers;

public:

	//p�lya ki�r�sa layerenk�nt
	//x, y koordin�ta player, a korl�toz�s miatt sz�ks�ges
	inline void Render(int x, int y) {
		for (unsigned int i = 0; i < GameMap_MapLayers.size(); i++) {
			GameMap_MapLayers[i]->Render(x, y);
		}
	}

	//p�lya friss�t�se layerenk�nt
	//x, y koordin�ta player, a korl�toz�s miatt sz�ks�ges
	inline void Update(int x, int y) {
		for (unsigned int i = 0; i < GameMap_MapLayers.size(); i++) {
			GameMap_MapLayers[i]->Update(x, y);
		}
	}

	//layerenk�nti felszabad�t�s
	inline void Clean() {
		for (auto i = 0; i < GameMap_MapLayers.size(); i++) {
			GameMap_MapLayers[i]->Clean();
			delete GameMap_MapLayers[i];
			GameMap_MapLayers[i] = nullptr;
		}
		GameMap_MapLayers.clear();
	}

	//map layer vektor pointer visszat�r�t�se
	inline std::vector<Layer*>* getMapLayers() { return &GameMap_MapLayers; }
};