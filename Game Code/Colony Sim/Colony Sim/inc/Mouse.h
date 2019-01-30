/*! \file This will manage the main functions for the mouse within the game. */

#pragma once

#include "defs.h"

/*! \class This class will be usd to maintain and manage mouse functions. */
class Mouse
{
	// Constructor 

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Mouse(); 

	// Deconstructor 

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~Mouse(); 

	// Data Members 

private:

	/*! \var This will hold the current position of the mouse in the game window. */
	sf::Vector2f m_MousePos;

	// Member Functions

public:

	//--------------------------------------------------------
	/*! \fn SetmousePos This will update the current mouse position. 
	*Param One : RenderWindow - The main game window.
	*/
	void m_SetMousePos(sf::RenderWindow &window); 

	//--------------------------------------------------------
	/*! \fn GetMousePos Used to return the value of the mouse position. 
	*
	*/
	sf::Vector2f m_GetMousePos(); 

};