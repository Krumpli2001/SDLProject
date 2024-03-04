#pragma once

struct Tileset;

class Layer {
private:
public:

	//ki�r�s
	virtual void Render(int x, int y) = 0;

	//friss�t�s
	virtual void Update(int x, int y) = 0;

	//t�rl�s/felszabad�t�s
	virtual void Clean() = 0;


	//visszaadja a blokkm�retet
	virtual int getTileSize() = 0;

	//visszaadja, hogy h�ny sor van a mapon
	virtual	int getRowCount() = 0;

	//visszaadja, hogy h�ny oszlop van a mapon
	virtual int getColCount() = 0;

	//visszaadja a tilemapot
	virtual std::vector<std::vector<int>>* getTileMap() = 0;

	//virtual std::vector<Tileset>* getTilesetVector() = 0;

};