#include "Button.h"
#include <string>


Button::Button(const char* buttonText, float x, float y, float width, float height, aie::Texture* img)
{
	//Store the text that will appear on the button.
	strcpy_s(m_buttonText, 64, buttonText);
	//Load a font to use to display the text.
	m_font = new aie::Font("./font/consolas.ttf", 24);
	
	//Store the button's position, width, and height.
	m_posX = x;
	m_posY = y;
	m_width = width;
	m_height = height;
	colourImg = img;
}
Button::~Button()
{
	delete m_font;
}


bool Button::Update()
{
	
	aie::Input* input = aie::Input::getInstance();
	//Get mouse position
	int mouseX = input->getMouseX();
	int mouseY = input->getMouseY();

	//Calculate the 4 sides of the button

	float left = m_posX - (m_width * 0.5f);
	float right = m_posX + (m_width * 0.5f);
	float bottom = m_posY - (m_height * 0.5f);
	float top = m_posY + (m_height * 0.5f);
	//Check if the mouse is inside the box made by the 4 sides.
	if (mouseX > left && mouseX < right &&
		mouseY > bottom && mouseY < top)
	{
		//Return whether the mouse button is clicked while colliding
		return input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT);
	}
	return false;


}

void Button::Draw(aie::Renderer2D* renderer)
{
	renderer->drawSprite(colourImg, m_posX, m_posY, m_width, m_height);


	//Calculating the centred text position is a bit fiddly.
	float textWidth = m_font->getStringWidth(m_buttonText);
	float textHeight = m_font->getStringHeight(m_buttonText);
	float centredPosX = m_posX - (textWidth * 0.5f) + 2;
	float centredPosY = m_posY - (textHeight * 0.5f) + 5;
	//Draw text on the button.
	renderer->drawText(m_font, m_buttonText, centredPosX, centredPosY);

}
