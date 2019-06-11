#include "ButtonApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>
#include <thread>
#include <chrono>
ButtonApp::ButtonApp() {

}

ButtonApp::~ButtonApp() {

}

//#define PLAYTEST

bool ButtonApp::startup() {

	strcpy_s(scoreTextDisplay, 64, "Score");
	m_2dRenderer = new aie::Renderer2D();
	correctCounter = 0;
	start = true;
	noConinueButtonInput = false;
	noButtonPress = true;
	list = new LinkedList;
	answerList = new LinkedList;
#ifdef PLAYTEST
	ball = new aie::Texture("textures/ball.png");
	yellow = new aie::Texture("textures/yellow.jpg");
	red = new aie::Texture("textures/Red.jpg");
	blue = new aie::Texture("textures/Blue.png");
	green = new aie::Texture("textures/Green.jpg");
	black = new aie::Texture("textures/black.jpg");
#else
	ball = new aie::Texture("../bin/textures/ball.png");
	yellow = new aie::Texture("../bin/textures/yellow.jpg");
	red = new aie::Texture("../bin/textures/Red.jpg");
	blue = new aie::Texture("../bin/textures/Blue.png");
	green = new aie::Texture("../bin/textures/Green.jpg");
	grey = new aie::Texture("../bin/textures/grey.png");
#endif
	m_continueButton = new Button("continue", 900, 100, 120, 50, grey);
	m_buttonYellow = new Button("", 350, 400, 120, 50, yellow);
	m_buttonBlue = new Button("", 500, 400, 120, 50, blue);
	m_buttonGreen = new Button("", 650, 400, 120, 50, green);
	m_buttonRed = new Button("", 800, 400, 120, 50, red);
	m_startButton = new Button("start", 580, 400, 120, 50, grey);
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"

#ifdef PLAYTEST
	m_font = new aie::Font("font/consolas.ttf", 32);
#else
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
#endif

	return true;
}

void ButtonApp::shutdown() {

	delete list;
	delete answerList;

	delete m_font;
	delete m_2dRenderer;

	delete m_buttonYellow;
	delete m_buttonBlue;
	delete m_buttonGreen;
	delete m_buttonRed;
	delete m_continueButton;
	delete m_startButton;

	delete yellow;
	delete red;
	delete blue;
	delete green;
	delete grey;
	delete ball;
}

void ButtonApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();
	if (m_startButton->Update() && (start == true))
	{
		start = false;
		notEnd = true;
		correctCounter = 0;
		noConinueButtonInput = false;
		noButtonPress = true;
		list->length = 0;
		answerList->length = 0;
		list->clearList();
		answerList->clearList();
		cout << list->length << endl;
	}
	if (m_continueButton->Update())
	{
		noConinueButtonInput = true;
		notCorrect = true;
		noButtonPress = true;
		cout << correctCounter << endl;
		cout << list->length << endl;
		if (correctCounter == list->length)
		{
			failInput = true;
			notEnd = true;
			Random();
			ballDraw();
			snprintf(charCorrectCounter, 64, "%s: %i ", scoreTextDisplay, correctCounter);
			
		}
		else
			failInput = false;
	}
	if (m_buttonYellow->Update() && (start == false))
	{
		answerList->add(0);
		cout << "answer" << endl;
		answerList->print();
		if (checkFail(notEnd))
			draw();

	}
	if (m_buttonBlue->Update() && (start == false))
	{
		answerList->add(1);
		cout << "answer" << endl;
		answerList->print();
		if (checkFail(notEnd))
			draw();
	}
	if (m_buttonGreen->Update() && (start == false))
	{
		answerList->add(2);
		cout << "answer" << endl;
		answerList->print();
		if (checkFail(notEnd))
			draw();
	}
	if (m_buttonRed->Update() && (start == false))
	{
		answerList->add(3);
		cout << "answer" << endl;
		answerList->print();
		if (checkFail(notEnd))
			draw();
	}

	// exit the application
	if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE))
	{
		//checks if its in the start menu or in game
		if (start == true)
			quit();
		else if (start == false)
		{
			start = true;
			noConinueButtonInput = false;
			list->clearList();
			answerList->clearList();
		}
	}
}

void ButtonApp::Random()
{
	list->add(rand() % 4);
	cout << "List" << endl;
	list->print();
}

//ballDraw function is a function that basically searches for the latest addition to the list and prints the ball in the location
//depending on the additions value (0-4)
//
void ButtonApp::ballDraw()
{
	int i = 0;
	//checks the value of the latest addition
	while (i < list->size())
	{
		if (list->search(list->size() - i) == 0)
		{
			//draws the ball in the location specified
			m_2dRenderer->drawSprite(ball, 350, 400);
		}
		else if (list->search(list->size() - i) == 1)
		{
			m_2dRenderer->drawSprite(ball, 500, 400);
		}
		else if (list->search(list->size() - i) == 2)
		{
			m_2dRenderer->drawSprite(ball, 650, 400);
		}
		else if (list->search(list->size() - i) == 3)
		{
			m_2dRenderer->drawSprite(ball, 800, 400);
		}
		++i;
	}
}

//the check fail function checks if the entire sequence the player has inputted matches the sequence that was randomally generated
//and also if it matches clears the players linkedlist for the next round
//
//input: bool &notEnd: a variable which is used to check if the player has failed or not 
//output: bool notEnd: used to end or continue the game and is used in if statements to draw up the fail screen
bool ButtonApp::checkFail(bool &notEnd)
{
	cout << "answerLength: " << answerList->length << endl;
	cout << "ListLength: " << list->length << endl;
	//checks if both of the lists are the same length so that when it is the same length it checks that both of the lists match
	if (answerList->length == list->length)
	{
		//checks if the lists are identical and stores it in the paramenter variable
		notEnd = answerList->areIdentical(answerList->head, list->head);
		//if the player didn't fail prepare the next round
		if (notEnd)
		{
			notCorrect = false;
			correctCounter++;
			failInput = true;
			draw();
		}
		answerList->clearList();
		answerList->length = 0;
	}
	else
	{
		//checks if the player pressed the continue button
		if (!noConinueButtonInput)
		{
			answerList->clearList();
			answerList->length = 0;
		}
	}
	return notEnd;
}


void ButtonApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	// draws up the menu screen
	if (start == true)
	{
		m_2dRenderer->begin();
		m_startButton->Draw(m_2dRenderer);
		m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 10);
		m_2dRenderer->drawText(m_font, "Simon Game", 495, 675);
		m_2dRenderer->drawText(m_font, "TEST YOUR MEMORY", 445, 600);
		m_2dRenderer->end();
	}
	else
	{
		
		m_2dRenderer->begin();
		//checks if the player has clicked the continue button
		if (!failInput)
		{
			m_2dRenderer->drawText(m_font, "must complete the sequence", 300, 600);
		}
		if (!notEnd)
		{
			//draws up the fail screen
			m_2dRenderer->drawText(m_font, "Failed", 550, 400);
			m_2dRenderer->drawText(m_font, charCorrectCounter, 535, 300);
			m_2dRenderer->drawText(m_font, "Press ESC to go back to menu", 0, 10);
			m_2dRenderer->end();
		}
		else
		{
			//draws up the game screen

			if (!notCorrect)
				m_2dRenderer->drawText(m_font, "Correct!!! press continue to add to the sequence", 300, 600);
			if (!noConinueButtonInput)
			{
				m_2dRenderer->drawText(m_font, "Must press continue to start", 300, 600);
			}

			//draws up the buttons for the game
			m_buttonYellow->Draw(m_2dRenderer);
			m_buttonBlue->Draw(m_2dRenderer);
			m_buttonRed->Draw(m_2dRenderer);
			m_buttonGreen->Draw(m_2dRenderer);
			m_continueButton->Draw(m_2dRenderer);
			//checks if the player has not failed
			if (notEnd)
			{
				int i = 0;
				//checks if the player has clicked the continue button to draw up the ball
				if (noConinueButtonInput)
				{
					while (i < list->size())
					{
						ballDraw();
						++i;
					}
				}

			}
			// output some text, uses the last used colour
			m_2dRenderer->drawText(m_font, "Press ESC to go back to menu", 0, 10);

			// done drawing sprites
			m_2dRenderer->end();
		}
	}
}