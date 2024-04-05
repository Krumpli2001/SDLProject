#pragma once

#include <SDL.h>

#include "CollisionHandler.hpp"

class Collider
{
private:
	SDL_Rect Collider_Box{};
	int tilesize = CollisionHandler::GetInstance()->getTileSize();
	std::vector<std::vector<std::pair<int, int>>> koords;
	std::vector<std::vector<std::pair<int, int>>> segedkoords;

public:
	Collider() {};
	Collider(int w, int h) {
		

		int i = 0;
		int j = 0;
		//Y
		koords.resize(static_cast<size_t>(std::ceil(static_cast<double>(h) / tilesize) + 1));
		//felso oldal
		for (int Y = 0; Y < h+tilesize; Y += tilesize) {
			//X
			if (Y == 0) {
				koords[i].resize(static_cast<size_t>(std::ceil(static_cast<double>(w) / tilesize) + 1));
			}
			else if (Y >= h) {
				koords[i].resize(static_cast<size_t>(std::ceil(static_cast<double>(w) / tilesize) + 1));
			}
			else {
				koords[i].resize(2);
			}

			j = 0;
			for (int X = 0; X < w+tilesize; X += tilesize) {

				if (Y == 0) {
					koords[i][j] = std::make_pair(X, Y);
					j++;
					//continue;
				}

				else if (Y >= h) {
					koords[i][j] = std::make_pair(X, h);
					j++;
					//continue;
				}

				else {
					if (X == 0 and Y > 0 and Y < h) {
						koords[i][j] = std::make_pair(X, Y);
						j++;
					}
					else if (X >= w and Y > 0 and Y < h) {
						koords[i][j] = std::make_pair(w, Y);
						j++;
					}
				}
			}
			i++;
		}

		////felso oldal
		//int X = 0;
		//while (X < w) {
		//	koords.push_back(std::make_pair(X, 0));
		//	X += tilesize;
		//}
		//koords.push_back(std::make_pair(w, 0));

		////also oldal
		//X = 0;
		//while (X < w) {
		//	koords.push_back(std::make_pair(X, h));
		//	X += tilesize;
		//}
		//koords.push_back(std::make_pair(w, h));

		////bal oldal
		//int Y = tilesize;
		//while (Y < h) {
		//	koords.push_back(std::make_pair(0, Y));
		//	Y += tilesize;
		//}
		//koords.push_back(std::make_pair(0, h));

		////jobb oldal
		//Y = 0;
		//while (Y < h) {
		//	koords.push_back(std::make_pair(w, Y));
		//	Y += tilesize;
		//}
		////koords.push_back(std::make_pair(w, h)); nem kell, ketszer lenne
	}

	//visszaadja a collider mereteit {x, y, w, h}
	inline SDL_Rect* getBox() { return &Collider_Box; }

	/*beállítja a collider méreteit
	x, y = felsõ bal sarok
	w, h = alsó jobb sarok*/ 
	inline void setBox(int x, int y, int w, int h) { 
		Collider_Box = { x, y, w, h };
	}
	inline auto getCollOldalak() { return &koords; }
	inline auto getSegedCollOldalak() { return &segedkoords; }
};