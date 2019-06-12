#include "Plane.h"



Plane::Plane()
{
}


Plane::~Plane()
{
}

Plane::Plane(Vector2& p1, Vector2& p2)
{
	auto v = p2 - p1;
	v.normalise();

	N.x = -v.y;
	N.y = v.x;

	m_d = -p1.dot(N);

}
float Plane::distanceTo(const Vector2& p)
{
	return p.dot(N) + m_d;
}
Vector2 Plane::closestPoint(Vector2& p)
{
	return p - N * distanceTo(p);
}
ePlaneResult Plane::testSide(const Vector2& p)
{
	float t = p.dot(N) + m_d;

	if (t < 0)
		return ePlaneResult::BACK;
	else if (t > 0)
		return ePlaneResult::FRONT;
	return ePlaneResult::INTERSECTS;
}
void Plane::collRes(Circle& circle)
{
	Vector2 tangent;
	tangent = distanceTo(circle.center);
	tangent.normalise();
	Vector2 relativeVelocity = Vector2(0 - circle.velocity.x, 0 - circle.velocity.y);
	float length = relativeVelocity.dot(tangent);
	Vector2 velocityComponent;
	velocityComponent = tangent * length;
	Vector2 velocityComponentPerpTangent = relativeVelocity - velocityComponent;
	circle.velocity.x += velocityComponent.x;
	circle.velocity.y += velocityComponent.y;
}
ePlaneResult Plane::testSide(const Circle& circle)
{
	float t = distanceTo(circle.center);
	if (t > circle.radius)
		return ePlaneResult::FRONT;
	else if (t < -circle.radius)
		return ePlaneResult::BACK;
	else
		return ePlaneResult::INTERSECTS;
}