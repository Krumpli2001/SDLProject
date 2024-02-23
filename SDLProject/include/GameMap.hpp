#pragma once

#include <vector>

#include "Layer.hpp"

class GameMap {
private:
	//friend class MapParser;
	std::vector<Layer*> GameMap_MapLayers;

public:
	inline void Render(int x, int y) {
		for (unsigned int i = 0; i < GameMap_MapLayers.size(); i++) {
			GameMap_MapLayers[i]->Render(x, y);
		}
	}

	inline void Update(int x, int y) {
		for (unsigned int i = 0; i < GameMap_MapLayers.size(); i++) {
			GameMap_MapLayers[i]->Update(x, y);
		}
	}

	inline void Clean() {
		for (auto i = 0; i < GameMap_MapLayers.size(); i++) {
			GameMap_MapLayers[i]->Clean();
			delete GameMap_MapLayers[i];
			GameMap_MapLayers[i] = nullptr;
		}
		GameMap_MapLayers.clear();
	}

	inline std::vector<Layer*>* getMapLayers() { return &GameMap_MapLayers; }
};