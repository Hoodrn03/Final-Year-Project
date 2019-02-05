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

public:

	// Member Functions 

	void m_InitGui(); 

	void m_HandleEvents(sf::Event &thisEvent);

	void m_DrawGui(sf::RenderWindow &window);

};