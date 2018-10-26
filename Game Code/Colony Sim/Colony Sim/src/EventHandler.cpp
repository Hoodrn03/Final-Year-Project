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
	}
}
