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
/*! \fn GetWindow : This will return the value of the window, this will for the window to be referenced oustide of the class. 
*
*/
sf::RenderWindow & Window::m_GetWindow()
{
	return m_Window; 
}

void Window::m_CheckForViewMove(int moveValue)
{
	switch (moveValue)
	{
	case 1: 
		m_MoveViewUp();
		break;

	case 2:
		m_MoveViewDown();
		break;

	case 3:
		m_MoveViewLeft();
		break;

	case 4:
		m_MoveViewRight();
		break;

	default:
		break;
	}

	m_Window.setView(m_GameView);
}

void Window::m_MoveViewUp()
{
	sf::Vector2f l_NewLocale = m_GameView.getCenter() + sf::Vector2f(0, -m_fViewMoveAmount); 

	m_GameView.setCenter(l_NewLocale); 
}

void Window::m_MoveViewDown()
{
	sf::Vector2f l_NewLocale = m_GameView.getCenter() + sf::Vector2f(0, m_fViewMoveAmount);

	m_GameView.setCenter(l_NewLocale);
}

void Window::m_MoveViewLeft()
{
	sf::Vector2f l_NewLocale = m_GameView.getCenter() + sf::Vector2f(-m_fViewMoveAmount, 0);

	m_GameView.setCenter(l_NewLocale);
}

void Window::m_MoveViewRight()
{
	sf::Vector2f l_NewLocale = m_GameView.getCenter() + sf::Vector2f(m_fViewMoveAmount, 0);

	m_GameView.setCenter(l_NewLocale);
}
