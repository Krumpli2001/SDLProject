#pragma once

class IObject {
private:
public:
	virtual void Draw(double scale = 1.0) = 0;
	virtual void Update(Uint64 dt) = 0;
	virtual void Clean() = 0;
};