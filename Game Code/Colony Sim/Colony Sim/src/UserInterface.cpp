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

	tgui::Button::Ptr l_NewButton = buttonToAdd; 

	m_Gui.add(l_NewButton); 

	std::cout << "Button Added" << std::endl;
}

void UserInterface::m_AddWidget(std::vector<tgui::Button::Ptr>& buttonsToAdd)
{
	if (buttonsToAdd.size() > 0)
	{
		for (unsigned int i = 0; i < buttonsToAdd.size(); i++)
		{
			tgui::Button::Ptr l_NewButton = buttonsToAdd[i];

			m_Gui.add(l_NewButton);

			std::cout << "Button Added" << std::endl;
		}
	}
}

void UserInterface::m_RemoveWidget(tgui::Button::Ptr & buttonToRemove)
{
	m_Gui.remove(buttonToRemove); 

	std::cout << "Button Removed" << std::endl;
}

void UserInterface::m_RemoveWidget(std::vector<tgui::Button::Ptr>& buttonsToRemove)
{
	if (buttonsToRemove.size() > 0)
	{
		for (unsigned int i = 0; i < buttonsToRemove.size(); i++)
		{
			m_Gui.remove(buttonsToRemove[i]);

			std::cout << "Button Removed" << std::endl;
		}
	}
}

void UserInterface::m_ClearAllWidgets()
{
	m_Gui.removeAllWidgets(); 
}
