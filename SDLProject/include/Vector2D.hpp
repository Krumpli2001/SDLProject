#pragma once

#include <iostream>

class Vector2D {
private:
	double Vector2D_X;
	double Vector2D_Y;
public:
	inline Vector2D(double x = 0.0, double y = 0.0) : Vector2D_X(x), Vector2D_Y(y) {}

	inline void setX(double x) {  Vector2D_X = x; }
	inline void setY(double y) {  Vector2D_Y = y; }

	inline double getX() { return Vector2D_X; }
	inline double getY() { return Vector2D_Y; }

	//muveletek
	inline Vector2D operator+(const Vector2D v2) const
	{
		return Vector2D(Vector2D_X + v2.Vector2D_X, Vector2D_Y + v2.Vector2D_Y);
	}

	inline Vector2D operator-(const Vector2D v2) const
	{
		return Vector2D(Vector2D_X - v2.Vector2D_X, Vector2D_Y - v2.Vector2D_Y);
	}

	inline Vector2D operator*(const double szorzat) const
	{
		return Vector2D(Vector2D_X * szorzat, Vector2D_Y * szorzat);
	}

	inline void log(std::string msg)
	{
		std::cout << msg << "(X, Y) = " << Vector2D_X << ", " << Vector2D_Y << std::endl;
	}

};