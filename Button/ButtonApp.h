#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Button.h"
#include "LinkedListDemo.h"
class ButtonApp : public aie::Application {
public:

	ButtonApp();
	virtual ~ButtonApp();

	virtual bool startup();
	virtual void shutdown();
	void Random();
	virtual void update(float deltaTime);
	virtual void draw();
	void ballDraw();
	bool checkFail(bool &notEnd);

protected:
	bool notEnd;
	bool notCorrect;
	bool start;
	bool noButtonPress;
	bool noConinueButtonInput;
	int correctCounter;
	bool failInput;
	char charCorrectCounter[64];
	char scoreTextDisplay[64];
	LinkedList* answerList;
	LinkedList* list;
	int randomNumber;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	Button* m_continueButton;
	Button* m_buttonYellow;
	Button* m_buttonBlue;
	Button* m_buttonRed;
	Button* m_buttonGreen;
	Button* m_startButton;
	aie::Texture* ball;
	aie::Texture* yellow;
	aie::Texture* grey;
	aie::Texture* blue;
	aie::Texture* red;
	aie::Texture* green;
};