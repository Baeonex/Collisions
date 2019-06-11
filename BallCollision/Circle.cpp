#include "Circle.h"
#include <algorithm>


Circle::Circle()
{
}


Circle::~Circle()
{
}

void Circle::fit(const Vector2* points, unsigned int count)
{
	Vector2 Min = { FLT_MAX, FLT_MAX };
	Vector2 Max = { FLT_MIN, FLT_MIN };

	for (unsigned int i = 0; i < count; ++i, ++points)
	{
		Min = min(Min, *points);
		Max = max(Max, *points);
	}

	center = (Min + Max) * 0.5f;
	radius = center.distance(Max);
}

void Circle::fit(const std::vector<Vector2>& points)
{
	Vector2 Min = { FLT_MAX,FLT_MAX };
	Vector2 Max = { FLT_MIN, FLT_MIN };

	for (auto& p : points)
	{
		Min = min(Min, p);
		Max = max(Max, p);
	}

	center = (Min + Max) * 0.5f;
	radius = center.distance(Max);
}
bool Circle::overlaps(Vector2 p) 
{
	Vector2 toPoint = p - center;
	return toPoint.magnitude() <= (radius * radius);
}
bool Circle::overlaps(Circle& other)
{
	Vector2 diff = center - other.center;

	float r = radius + other.radius;
	return diff.magnitude() <= (r * r);
}
Vector2 Circle::closestPoint(Vector2 p) const
{
	Vector2 toPoint = p - center;

	if (toPoint.magnitude() > radius)
	{
		toPoint = toPoint.normalise() * radius;
	}

	return center + toPoint;
}