#include "UserInterface.h"

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

void UserInterface::m_InitGui(sf::RenderWindow & window)
{
	m_Gui.setTarget(window);
}

void UserInterface::m_HandleEvents(sf::Event & thisEvent)
{
	m_Gui.handleEvent(thisEvent);
}

void UserInterface::m_DrawGui()
{
	m_Gui.draw(); 
}

void UserInterface::m_AddWidget(tgui::Button::Ptr & buttonToAdd)
{

	tgui::Button::Ptr l_NewButton = buttonToAdd; 

	m_Gui.add(l_NewButton); 

	std::cout << "Button Added" << std::endl;
}

void UserInterface::m_ClearAllWidgets()
{
	m_Gui.removeAllWidgets(); 
}
