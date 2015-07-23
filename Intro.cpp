#include "Intro.h"

//Constructor
Intro::Intro()
{
	//Load background - exit if it fails
	m_background = load_bitmap("Images/IntroBG.bmp", 0);

	if(!m_background)
	{
		allegro_message("INTRO BACKGROUND BITMAP");
		exit(1);
	}

	m_stateID = STATE_INTRO;
}

void Intro::HandleEvents()
{
	//Move to Title Screen if mouse is clicked
	if(mouse_b & 1)
	{
		m_nextState = STATE_TITLE;
	}
}

void Intro::Logic()
{

}

void Intro::Render()
{
	//Draw necessary objects
	blit(m_background, m_buffer, 0, 0, 0, 0, m_background->w, m_background->h);
	blit(m_buffer, screen, 0, 0, 0, 0, m_buffer->w, m_buffer->h);
}

//Destructor
Intro::~Intro()
{

}