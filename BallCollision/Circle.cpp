#include "Circle.h"
#include <algorithm>
#include <iostream>

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
	return toPoint.magnitude() <= (radius);
}
bool Circle::overlaps(Circle& other)
{
	Vector2 diff = center - other.center;
	float r = radius + other.radius;
	
	if (diff.magnitude() <= (r))
	{
	
		Vector2 tangentVector;
		tangentVector.y = -(other.center.x - center.x);
		tangentVector.x = (other.center.y - center.y);
		tangentVector.normalise();
		Vector2 relativeVelocity = Vector2(velocity.x - other.velocity.x, velocity.y - other.velocity.y);
		float length = relativeVelocity.dot(tangentVector);
		Vector2 velocityComponent;
		velocityComponent = tangentVector * length;
		Vector2 velocityComponentPerpToTangent = relativeVelocity - velocityComponent;
		circleMove(velocityComponentPerpToTangent, other);

	}
	
	return diff.magnitude() <= (r);
}
void Circle::circleMove(Vector2 move, Circle& other)
{
	velocity.x -= move.x;
	velocity.y -= move.y;
	other.velocity.x += move.x;
	other.velocity.y += move.y;
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