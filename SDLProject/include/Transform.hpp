#pragma once

#include "Vector2D.hpp"

class Transform {
private:
	double Transform_X;
	double Transform_Y;

public:
	inline Transform(double x = 0.0, double y = 0.0) : Transform_X(x), Transform_Y(y) {}

	inline double getX() const { return Transform_X; }
	inline double getY() const { return Transform_Y; }

	inline void setX(double X) { Transform_X = X; }
	inline void setY(double Y) { Transform_Y = Y; }

	inline void tX(double x) { Transform_X += x; }
	inline void tY(double y) { Transform_Y += y; }
	inline void tr(Vector2D v) { Transform_X += v.getX(); Transform_Y += v.getY(); }

	inline void log(std::string msg) const
	{
		std::cout << msg << "(X, Y) = " << Transform_X << ", " << Transform_Y << std::endl;
	}
};