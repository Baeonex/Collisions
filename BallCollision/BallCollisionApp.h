#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "MathLib4.h"
#include "Circle.h"
#include <iostream>
#include "Box.h"
#include <vector>
#include "Ray.h"
#include "Plane.h"
class BallCollisionApp : public aie::Application {
public:

	BallCollisionApp();
	virtual ~BallCollisionApp();

	virtual bool startup();
	virtual void shutdown();
	void borderLengths();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Renderer2D* ballRenderer;
	aie::Font*			m_font;
	Box box;
	Circle circle;
	Circle stat;
	Vector2 point;
	Vector2 v;
	Vector2* I;
	Vector2* R;
	Plane borderLeft;
	Plane plane;
	Plane borderRight;
	Plane borderTop;
	Plane borderBottom;
	Vector2 p1;
	Vector2 p2;
	ePlaneResult side;
	int height;
	int width;
	Ray m_ray;
	std::vector<Circle> balls;
	int ballCount;
	bool newBall;
};