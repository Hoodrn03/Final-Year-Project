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

		m_CheckForMouseWheel();
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
			m_bMoveViewUp = true; 
		}
		else if (m_Event.key.code == m_ViewDown)
		{
			m_bMoveViewDown = true;
		}
		else if (m_Event.key.code == m_ViewLeft)
		{
			m_bMoveViewLeft = true;
		}
		else if (m_Event.key.code == m_ViewRight)
		{
			m_bMoveViewRight = true;
		}
	}

	else if (m_Event.type == sf::Event::KeyReleased)
	{
		if (m_Event.key.code == m_ViewUp)
		{
			m_bMoveViewUp = false;
		}
		else if (m_Event.key.code == m_ViewDown)
		{
			m_bMoveViewDown = false;
		}
		else if (m_Event.key.code == m_ViewLeft)
		{
			m_bMoveViewLeft = false;
		}
		else if (m_Event.key.code == m_ViewRight)
		{
			m_bMoveViewRight = false;
		}
	}
}

//--------------------------------------------------------
/*! \fn Check View Up Value : This will be used to check if the up key was pressed.
*
*/
bool EventHandler::m_CheckViewUpValue()
{
	return m_bMoveViewUp;
}

//--------------------------------------------------------
/*! \fn Check View Down Value : This will be used to check if the down key was pressed.
*
*/
bool EventHandler::m_CheckViewDownValue()
{
	return m_bMoveViewDown;
}

//--------------------------------------------------------
/*! \fn Check View Left Value : This will be used to check if the left key was pressed.
*
*/
bool EventHandler::m_CheckViewLeftValue()
{
	return m_bMoveViewLeft;
}

//--------------------------------------------------------
/*! \fn Check View Right Value : This will be used to check if the right key was pressed.
*
*/
bool EventHandler::m_CheckViewRightValue()
{
	return m_bMoveViewRight;
}

//--------------------------------------------------------
/*! \fn Check For Mouse Wheel : This will check to see if the mouse wheel has been moved.
*
*/
void EventHandler::m_CheckForMouseWheel()
{
	if (m_Event.type == sf::Event::MouseWheelMoved)
	{
		if (m_Event.mouseWheel.delta >= 1)
		{
			m_iMouseWheelState = 1;
		}
		else if (m_Event.mouseWheel.delta <= -1)
		{
			m_iMouseWheelState = -1;
		}
	}


}


//--------------------------------------------------------
/*! \fn Get Mouse Wheel State : This will be used to return the state of the mouse wheel.
*
*/
int & EventHandler::m_GetMouseWheelState()
{
	return m_iMouseWheelState;
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
/*! \fn Current layer change value : Will return the layer change key value.
*
*/
int & EventHandler::m_CurrentLayerChangeValue()
{
	return m_iLayerMoveValue;
}
