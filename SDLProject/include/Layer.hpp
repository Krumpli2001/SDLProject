#pragma once

struct Tileset;

class Layer {
private:
public:

	//kiírás
	virtual void Render(int x, int y) = 0;

	//frissítés
	virtual void Update(int x, int y) = 0;

	//törlés/felszabadítás
	virtual void Clean() = 0;


	//visszaadja a blokkméretet
	virtual int getTileSize() = 0;

	//visszaadja, hogy hány sor van a mapon
	virtual	int getRowCount() = 0;

	//visszaadja, hogy hány oszlop van a mapon
	virtual int getColCount() = 0;

	//visszaadja a tilemapot
	virtual std::vector<std::vector<int>>* getTileMap() = 0;

	//virtual std::vector<Tileset>* getTilesetVector() = 0;

};