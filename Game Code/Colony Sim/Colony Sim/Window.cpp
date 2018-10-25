/*! \file Window.cpp
*
* This will hold all of the definitions for the class window. 
*
*/

#include "Window.h"

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
/*! \fn InitWindow :- This will create the game window, if there is any errors returns 1 else returns 0;
*Param One : int - The width for the game window.
*Param Two : int - The height for the game window.
*Param Three : string - The name for the window.
*/
int Window::m_InitWindow(int windowWidth, int windowHeight, std::string windowName)
{
	try
	{
		m_Window.create(sf::VideoMode(windowWidth, windowHeight), windowName); 
	}
	catch(const std::exception& e)
	{
		std::cout << "Unable to create window : " << e.what() << std::endl;
	}

	return 0;
}

sf::RenderWindow & Window::m_GetWindow()
{
	return m_Window; 
}
