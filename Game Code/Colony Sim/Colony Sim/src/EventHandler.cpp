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
		window.setKeyRepeatEnabled(false); 

		// Event : Check for window close. 
		if (m_Event.type == sf::Event::Closed)
		{
			std::cout << "Window Closed" << std::endl;

			window.close(); 
		}

		m_CheckForViewMoveKeys(); 

		m_CheckForLayerChange(); 
	}
}

//--------------------------------------------------------
/*! \fn Check for view move keys : This will be used to see if a movement key was pressed this frame.
*
*/
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

//--------------------------------------------------------
/*! \fn Check for layer change : This will see if a layer chnage key was pressed.
*
*/
void EventHandler::m_CheckForLayerChange()
{
	if (m_Event.type == sf::Event::KeyPressed)
	{
		if (m_Event.key.code == m_LayerUp)
		{
			m_iLayerMoveValue = 1;

		}
		else if (m_Event.key.code == m_LayerDown)
		{
			m_iLayerMoveValue = 2;

		}
	}
	else
	{
		m_iLayerMoveValue = 0;
	}
}

//--------------------------------------------------------
/*! \fn Check view move value : Will return the current movemnt key value.
*
*/
int EventHandler::m_CurentViewMoveValue()
{
	return m_iViewMoveValue;
}

//--------------------------------------------------------
/*! \fn Current layer change value : Will return the layer change key value.
*
*/
int & EventHandler::m_CurrentLayerChangeValue()
{
	return m_iLayerMoveValue;
}
