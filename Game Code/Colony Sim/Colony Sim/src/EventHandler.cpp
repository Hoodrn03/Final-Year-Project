/*! \file EventHandler.cpp
*
* This will hold all of the definitions for the class EventHandler.
*
*/

#include "../inc/EventHandler.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
EventHandler::EventHandler()
{
}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
EventHandler::~EventHandler()
{
}

//--------------------------------------------------------
/*! \fn CheckForEvents : This will be used to process any events which happened during this loop.
*Param One : RenderWindow - This will be the current game window.
*/
void EventHandler::m_CheckForEvents(sf::RenderWindow & window)
{
	while (window.pollEvent(m_Event))
	{

		// Event : Check for window close. 
		if (m_Event.type == sf::Event::Closed)
		{
			std::cout << "Window Closed" << std::endl;

			window.close(); 
		}

		m_CheckForViewMoveKeys(); 
	}
}

void EventHandler::m_CheckForViewMoveKeys()
{
	if (m_Event.type == sf::Event::KeyPressed)
	{
		if (m_Event.key.code == m_ViewUp)
		{
			m_iViewMoveValue = 1; 
		}
		else if (m_Event.key.code == m_ViewDown)
		{
			m_iViewMoveValue = 2;
		}
		else if (m_Event.key.code == m_ViewLeft)
		{
			m_iViewMoveValue = 3;
		}
		else if (m_Event.key.code == m_ViewRight)
		{
			m_iViewMoveValue = 4;
		}
	}
	else if (m_Event.type == sf::Event::KeyReleased)
	{
		m_iViewMoveValue = 0;
	}
}

int EventHandler::m_CurentViewMoveValue()
{
	return m_iViewMoveValue;
}
