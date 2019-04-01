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

void UserInterface::m_HandleEvents(sf::Event & ThisEvent)
{
	m_Gui.handleEvent(ThisEvent);
}

void UserInterface::m_DrawGui()
{
	m_Gui.draw(); 
}

void UserInterface::m_AddWidget(tgui::Button::Ptr & buttonToAdd)
{ 
	m_Gui.add(buttonToAdd);
}

void UserInterface::m_AddWidget(std::vector<tgui::Button::Ptr>& buttonsToAdd)
{
	if (buttonsToAdd.size() > 0)
	{
		for (unsigned int i = 0; i < buttonsToAdd.size(); i++)
		{
			m_Gui.add(buttonsToAdd[i]);
		}
	}
}

void UserInterface::m_RemoveWidget(tgui::Button::Ptr & buttonToRemove)
{
	m_Gui.remove(buttonToRemove); 
}

void UserInterface::m_RemoveWidget(std::vector<tgui::Button::Ptr>& buttonsToRemove)
{
	if (buttonsToRemove.size() > 0)
	{
		for (unsigned int i = 0; i < buttonsToRemove.size(); i++)
		{
			m_Gui.remove(buttonsToRemove[i]);
		}
	}
}

void UserInterface::m_ClearAllWidgets()
{
	m_Gui.removeAllWidgets(); 
}
