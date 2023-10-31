#pragma once

class Layer {
private:
public:
	virtual void Render(double scale) = 0;
	virtual void Update() = 0;

	virtual int getTileSize() = 0;
	virtual	int getRowCount() = 0;
	virtual int getColCount() = 0;
};