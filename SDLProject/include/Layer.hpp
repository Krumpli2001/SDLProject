#pragma once

class Layer {
private:
public:
	virtual void Render(int x, int y) = 0;
	virtual void Update(int x, int y) = 0;
	virtual void Clean() = 0;

	virtual int getTileSize() = 0;
	virtual	int getRowCount() = 0;
	virtual int getColCount() = 0;
};