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

	

	sfg::SFGUI m_Gui; 

	sfg::Desktop m_Desktop; 

	sfg::Window::Ptr m_Window; 

	

public:

	// Member Functions 

	void m_InitGui(); 

	void m_HandleEvents(sf::Event &thisEvent);

	void m_DrawGui(sf::RenderWindow &window);

};