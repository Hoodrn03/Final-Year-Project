#pragma once

#include "defs.h"

class UserInterface
{
public:

	UserInterface();

public: 

	~UserInterface();

private:

	// Data Members 

	tgui::Gui m_Gui; 

public:

	// Member Functions 

	void m_InitGui(sf::RenderWindow &window); 

	void m_HandleEvents(sf::Event &thisEvent);

	void m_DrawGui();

	void m_AddWidget(tgui::Button::Ptr &buttonToAdd); 

	void m_ClearAllWidgets(); 

};