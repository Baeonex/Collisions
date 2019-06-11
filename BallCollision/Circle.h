#pragma once
#include "MathLib4.h"
#include <float.h>
#include <vector>
class Circle
{
public:
	Circle();
	Circle(const Vector2& p, float r) : center(p), radius(r) {}
	~Circle();
	float min(float a, float b) { return  a < b ? a : b; }
	float max(float a, float b) { return a > b ? a : b; }
	Vector2 min(const Vector2& a, const Vector2& b) 
	{
		return { min(a.x,b.x), min(a.y, b.y) };
	}
	Vector2 max(const Vector2& a, const Vector2& b)
	{
		return { max(a.x,b.x), max(a.y, b.y) };
	}
	Vector2 center;
	float radius;
	void fit(const Vector2* points, unsigned int count);
	void fit(const std::vector<Vector2>& points);
	bool overlaps(Vector2 p);
	bool overlaps(Circle& other);
	Vector2 closestPoint(Vector2 p) const;
};

