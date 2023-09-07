#pragma once

#include <iostream>

class Point
{
private:
	int Point_X;
	int Point_Y;
public:
	inline Point(int x = 0, int y = 0) : Point_X(x), Point_Y(y) {};

	inline int getX() { return Point_X; }
	inline int getY() { return Point_Y; }

	inline double setX(double x) { return Point_X = x; }
	inline double setY(double y) { return Point_Y = y; }


	inline Point operator+(const Point& p2) const {
		return Point(Point_X + p2.Point_X, Point_Y + p2.Point_Y);
	}

	inline friend Point operator+=(Point& p1, const Point& p2) {
		p1.Point_X += p2.Point_X;
		p1.Point_Y += p2.Point_Y;
		return p1;
	}

	inline Point operator-(const Point& p2) const {
		return Point(Point_X - p2.Point_X, Point_Y - p2.Point_Y);
	}

	inline friend Point operator-=(Point& p1, const Point& p2) {
		p1.Point_X -= p2.Point_X;
		p1.Point_Y -= p2.Point_Y;
		return p1;
	}

	inline Point operator*(const double scalar) const {
		return Point(Point_X * scalar, Point_Y * scalar);
	}

	inline void Log(std::string msg) {
		std::cout << msg << "(X, Y) = (" << Point_X << " " << Point_Y << ")\n";
	}
};