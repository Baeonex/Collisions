#include "BallCollisionApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <random>
BallCollisionApp::BallCollisionApp() {

}

BallCollisionApp::~BallCollisionApp() {

}

bool BallCollisionApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	circle.center.x = 200;
	circle.center.y = 200;
	circle.radius = 20;
	stat.center.x = 600;
	stat.center.y = 600;
	stat.radius = 20;
	borderLengths();
	stat.velocity.x = 10;
	stat.velocity.y = -10;
	newBall = false;
	Vector2 n = { 640,360 };
	point = plane.closestPoint(n);
	p1 = plane.closestPoint(Vector2(0,0));
	p2 = plane.closestPoint(Vector2(height, width));

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void BallCollisionApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void BallCollisionApp::borderLengths()
{
	height = aie::Application::getWindowHeight();
	width = aie::Application::getWindowWidth();
	borderLeft = { 1,0,0 };
	borderRight = { -1,0, (float)width };
	//borderTop = { (float)width / 2, (float)height, (float)width };
	borderTop = { 0, -1, (float)height };
	borderBottom = { 0, 1, 0 };
}

void BallCollisionApp::update(float deltaTime) {

	// input example
	borderLengths();
	aie::Input* input = aie::Input::getInstance();
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		for (int i = 0; i < balls.size(); ++i)
		{
			balls[i].center.y += 200 * deltaTime;
			balls[i].center.x += balls[i].velocity.x * deltaTime;
		}
		for (int i = 0; i < balls.size(); ++i)
		{
			v = balls[i].closestPoint(point);
			//std::cout << point.distance(v) << std::endl;
		}
	}
	stat.center.y += stat.velocity.y * deltaTime;
	stat.center.x += stat.velocity.x * deltaTime;
	for (int i = 0; i < balls.size(); ++i)
	{
		balls[i].center.y += balls[i].velocity.y * deltaTime;
		balls[i].center.x += balls[i].velocity.x * deltaTime;
		balls[i].overlaps(stat) * deltaTime;

		if (borderLeft.testSide(balls[i]) == ePlaneResult::INTERSECTS)
		{
			borderLeft.collRes(balls[i]);
			std::cout << "plane1" << std::endl;
		}
		if (borderRight.testSide(balls[i]) == ePlaneResult::INTERSECTS)
			std::cout << "plane2" << std::endl;
		if (borderTop.testSide(balls[i]) == ePlaneResult::INTERSECTS)
			std::cout << "plane3" << std::endl;
		if (borderBottom.testSide(balls[i]) == ePlaneResult::INTERSECTS)
			std::cout << "plane4" << std::endl;
		if (plane.testSide(balls[i]) == ePlaneResult::INTERSECTS)
			std::cout << "plane5" << std::endl;
	}
	for (int i = 0; i < balls.size(); ++i)
	{
		if (balls.size() != 1)
		{
			for (int j = i + 1; j < balls.size(); ++j)
			{
				balls[i].overlaps(balls[j]);
			}
		}
	}
	for (int i = 1; i < balls.size(); ++i)
	{
		if (i == (balls.size() - i))
			continue;
		else if (balls.size() == 1)
			continue;
		else
			balls[i].overlaps(balls[balls.size() - i]);
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		for (int i = 0; i < balls.size(); ++i)
		{
			balls[i].center.y += balls[i].velocity.y * deltaTime;
		}
		for (int i = 0; i < balls.size(); ++i)
		{
			v = balls[i].closestPoint(point);
			//std::cout << point.distance(v) << std::endl;
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		for (int i = 0; i < balls.size(); ++i)
		{
			balls[i].center.x += 200 * deltaTime;
		}
		for (int i = 0; i < balls.size(); ++i)
		{
			v = balls[i].closestPoint(point);
			std::cout << point.distance(v) << std::endl;
		}
	}
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		for (int i = 0; i < balls.size(); ++i)
		{
			balls[i].center.x += -200 * deltaTime;
		}
		for (int i = 0; i < balls.size(); ++i)
		{
			v = balls[i].closestPoint(point);
			std::cout << point.distance(v) << std::endl;
		}
	}
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		
		float mouseX = input->getMouseX();
		float mouseY = input->getMouseY();
		circle.center.x = mouseX;
		circle.center.y = mouseY;
		circle.velocity.x = (rand() % 200 - 100);
		circle.velocity.y = (rand() % 200 - 100);
		
		balls.push_back(circle);
		for (int i = 0; i < balls.size(); ++i)
		{
			v = balls[i].closestPoint(point);
			//std::cout << point.distance(v) << std::endl;
		}

	}
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}



void BallCollisionApp::draw() {


	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	//m_2dRenderer->drawLine(p1.x, p1.y, p2.x, p2.y, 6);
	for (int i = 0; i < balls.size(); ++i)
	{
		m_2dRenderer->drawCircle(balls[i].center.x, balls[i].center.y, circle.radius);
	}
	//m_2dRenderer->drawCircle(point.x, point.y, 5);
	//m_2dRenderer->drawLine(m_ray.origin.x, m_ray.origin.y, m_ray.origin.x + m_ray.direction.x * m_ray.length, m_ray.origin.y + m_ray.direction.y * m_ray.length, 5);
	m_2dRenderer->drawCircle(stat.center.x, stat.center.y, stat.radius);
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}