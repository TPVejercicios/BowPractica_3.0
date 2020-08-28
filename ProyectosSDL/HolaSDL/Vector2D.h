#pragma once
#include "checkML.h"

using namespace std;
//using Point2D = Vector2D;

class Vector2D {
private:
	double X = 0;
	double Y = 0;

public:
	Vector2D() {};
	Vector2D(double x, double y) { X = x; Y = y; };

	double getX() const { return X; };
	double getY() const { return Y; };
	void setX(double valor) { X = valor; };
	void setY(double valor) { Y = valor; };
	void subVectorInY(Vector2D vel) { Y -= vel.Y; };
	void multiply(double n) { X* n; Y* n; };
	void normalize();
	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator*(double d) const;
	double operator*(const Vector2D& d) const;
};

