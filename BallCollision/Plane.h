#pragma once
#include "MathLib4.h"
#include "Circle.h"

enum ePlaneResult : int {
	FRONT = 1,
	BACK = -1,
	INTERSECTS = 0
};

class Plane
{
public:
	Plane();
	Plane(float x,float y, float d) : N(x,y), m_d(d) {}
	Plane(const Vector2& n, float d) : N(n), m_d(d) {}
	Plane(Vector2& p1, Vector2& p2);
	float distanceTo(const Vector2& p);
	Vector2 closestPoint(Vector2& p);
	ePlaneResult testSide(const Vector2& p);
	void collRes(Circle& circle);
	ePlaneResult testSide(const Circle& circle);
	~Plane();
	Vector2 N;
	float m_d;

};

