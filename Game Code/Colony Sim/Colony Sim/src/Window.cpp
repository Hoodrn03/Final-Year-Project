/*! \file Window.cpp
*
* This will hold all of the definitions for the class window. 
*
*/

#include "../inc/Window.h"

//--------------------------------------------------------
/*! \fn Constructor 
*
*/
Window::Window()
{
}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
Window::~Window()
{
}

//--------------------------------------------------------
/*! \fn InitWindow : This will create the game window, if there is any errors returns 1 else returns 0;
*Param One : int - The width for the game window.
*Param Two : int - The height for the game window.
*Param Three : string - The name for the window.
*/
int Window::m_InitWindow(int windowWidth, int windowHeight, std::string windowName)
{
	try
	{
		m_Window.create(sf::VideoMode(windowWidth, windowHeight), windowName); 

		m_GameView.setSize(400, 400); 

		m_GameView.setCenter(m_GameView.getSize().x * 0.5f, m_GameView.getSize().y * 0.5f);

		m_Window.setView(m_GameView);

	}
	catch(const std::exception& e)
	{
		std::cout << "Unable to create window : " << e.what() << std::endl;
	}

	return 0;
}

//--------------------------------------------------------
/*! \fn GetWindow : This will return the value of the window, This will for the window to be referenced oustide of the class. 
*
*/
sf::RenderWindow & Window::m_GetWindow()
{
	return m_Window; 
}

sf::Vector2f Window::m_GetViewSize()
{
	return m_GameView.getSize();
}

//--------------------------------------------------------
/*! \fn GetViewUpperBounds : This will return the top left of the game view.
*
*/
sf::Vector2f Window::m_GetViewUpperBounds()
{
	return sf::Vector2f(m_GameView.getCenter().x - (m_GameView.getSize().x * 0.5f), m_GameView.getCenter().y - (m_GameView.getSize().y * 0.5f)); 
}

//--------------------------------------------------------
/*! \fn GetViewLowerBounds : Thiis will return the bottom right of the game view.
*
*/
sf::Vector2f Window::m_GetViewLowerBounds()
{
	return sf::Vector2f(m_GameView.getCenter().x + (m_GameView.getSize().x * 0.5f), m_GameView.getCenter().y + (m_GameView.getSize().y * 0.5f));
}

//--------------------------------------------------------
/*! \fn CheckForViewMove : This will b eused to check if the view should be moved This frame.
*Param One : int - The current key being pressed, if none are pressed it recives 0.
*/
void Window::m_CheckForViewMove(bool upValue, bool downValue, bool leftValue, bool rightValue)
{
	if (upValue == true)
	{
		m_ViewMoveVector += sf::Vector2f(0, -m_fViewMoveAmount); 
	}
	else if (downValue == true)
	{
		m_ViewMoveVector += sf::Vector2f(0, m_fViewMoveAmount);
	}
	else
	{
		m_ViewMoveVector = sf::Vector2f(m_ViewMoveVector.x, 0);
	}

	if (leftValue == true)
	{
		m_ViewMoveVector += sf::Vector2f(-m_fViewMoveAmount, 0);
	}
	else if (rightValue == true)
	{
		m_ViewMoveVector += sf::Vector2f(m_fViewMoveAmount, 0); 
	}
	else
	{
		m_ViewMoveVector = sf::Vector2f(0, m_ViewMoveVector.y);
	}

	if (m_ViewMoveVector.x > m_fViewMoveAmount)
	{
		m_ViewMoveVector.x = m_fViewMoveAmount; 
	}
	else if (m_ViewMoveVector.x < -m_fViewMoveAmount)
	{
		m_ViewMoveVector.x = -m_fViewMoveAmount;
	}

	if (m_ViewMoveVector.y > m_fViewMoveAmount)
	{
		m_ViewMoveVector.y = m_fViewMoveAmount;
	}
	else if (m_ViewMoveVector.y < -m_fViewMoveAmount)
	{
		m_ViewMoveVector.y = -m_fViewMoveAmount;
	}

	m_GameView.setCenter(m_GameView.getCenter() + m_ViewMoveVector); 

	m_Window.setView(m_GameView);
}

//--------------------------------------------------------
/*! \fn Check for View Scroll : This will be used to updte the size of the view based on the direction the mouse wheel is turned.
*Param One : int - The value for the mouse wheel, it will allow the distinction between up and down, as well as idle.
*/
void Window::m_CheckForViewScroll(int & mouseWheelValue)
{
	switch (mouseWheelValue)
	{
	case 0:
		break;

	case 1:
		
		if (m_GameView.getSize().x - m_fScrollAmount > m_MinScrollAmount.x &&
			m_GameView.getSize().y - m_fScrollAmount > m_MinScrollAmount.y)
		{
			m_GameView.setSize(m_GameView.getSize() + sf::Vector2f(-m_fScrollAmount, -m_fScrollAmount));
		}

		break;

	case -1:

		if (m_GameView.getSize().x - m_fScrollAmount < m_MaxScrollAmount.x &&
			m_GameView.getSize().y - m_fScrollAmount < m_MaxScrollAmount.y)
		{
			m_GameView.setSize(m_GameView.getSize() + sf::Vector2f(m_fScrollAmount, m_fScrollAmount));
		}

		break;

	default:
		break;
	}

	mouseWheelValue = 0;
}

//--------------------------------------------------------
/*! \fn MoveViewUp : Moves the view in a direction.
*
*/
void Window::m_MoveViewUp()
{
	sf::Vector2f l_NewLocale = m_GameView.getCenter() + sf::Vector2f(0, -m_fViewMoveAmount); 

	m_GameView.setCenter(l_NewLocale); 
}

//--------------------------------------------------------
/*! \fn MoveViewDown : Moves the view in a direction.
*
*/
void Window::m_MoveViewDown()
{
	sf::Vector2f l_NewLocale = m_GameView.getCenter() + sf::Vector2f(0, m_fViewMoveAmount);

	m_GameView.setCenter(l_NewLocale);
}

//--------------------------------------------------------
/*! \fn MoveViewLeft : Moves the view in a direction.
*
*/
void Window::m_MoveViewLeft()
{
	sf::Vector2f l_NewLocale = m_GameView.getCenter() + sf::Vector2f(-m_fViewMoveAmount, 0);

	m_GameView.setCenter(l_NewLocale);
}
//--------------------------------------------------------
/*! \fn MoveViewRight : Moves the view in a direction.
*
*/
void Window::m_MoveViewRight()
{
	sf::Vector2f l_NewLocale = m_GameView.getCenter() + sf::Vector2f(m_fViewMoveAmount, 0);

	m_GameView.setCenter(l_NewLocale);
}
