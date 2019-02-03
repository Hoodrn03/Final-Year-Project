#include "UserInterface.h"



UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}



void UserInterface::m_InitGui()
{
	 m_Window = sfg::Window::Create();

	 m_Desktop.Add(m_Window); 
}

void UserInterface::m_HandleEvents(sf::Event & thisEvent)
{
	m_Desktop.HandleEvent(thisEvent);
}

void UserInterface::m_DrawGui(sf::RenderWindow & window)
{
	m_Gui.Display(window); 
}

