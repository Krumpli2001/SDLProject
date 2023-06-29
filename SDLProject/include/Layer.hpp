#pragma once

class Layer {
private:
public:
	virtual void Render() = 0;
	virtual void Update() = 0;
};