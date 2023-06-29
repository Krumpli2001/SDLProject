#pragma once

#include <vector>

#include "Layer.hpp"

class GameMap {
private:
	friend class MapParser;
	std::vector<Layer*> GameMap_MapLayers;

public:
	inline void Render() {
		for (unsigned int i = 0; i < GameMap_MapLayers.size(); i++) {
			GameMap_MapLayers[i]->Render();
		}
	}

	inline void Update() {
		for (unsigned int i = 0; i < GameMap_MapLayers.size(); i++) {
			GameMap_MapLayers[i]->Update();
		}
	}

	inline std::vector<Layer*> getMapLayers() { return GameMap_MapLayers; }
};