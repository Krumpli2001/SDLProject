#pragma once

class IObject {
private:
public:
	virtual void Draw() = 0;
	virtual void Update(double dt) = 0;
	virtual void Clean() = 0;
};