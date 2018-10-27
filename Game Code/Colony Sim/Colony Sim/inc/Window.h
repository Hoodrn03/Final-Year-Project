/*! \file Window.h
*
* This class will control all functons regarding the game window and 
* the game view for that window. 
*
*/

#pragma once

#include "defs.h"

class Window
{

public:
	
	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Window();

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~Window(); 

	// Data Members 

private:

	/*! \var This will be the main game window for the game. */
	sf::RenderWindow m_Window;

	sf::View m_GameView; 

	float m_fViewMoveAmount = 1.f; 

	// Member Functions

public: 

	//--------------------------------------------------------
	/*! \fn InitWindow :- This will create the game window, if there is any errors returns 1 else returns 0; 
	*Param One : int - The width for the game window. 
	*Param Two : int - The height for the game window. 
	*Param Three : string - The name for the window. 
	*/
	int m_InitWindow(int windowWidth, int windowHeight, std::string windowName); 

	//--------------------------------------------------------
	/*! \fn GetWindow : This will return the value of the window, this will for the window to be referenced oustide of the class.
	*
	*/
	sf::RenderWindow & m_GetWindow(); 

	void m_CheckForViewMove(int moveValue);

	void m_MoveViewUp();

	void m_MoveViewDown(); 

	void m_MoveViewLeft(); 

	void m_MoveViewRight(); 

};
