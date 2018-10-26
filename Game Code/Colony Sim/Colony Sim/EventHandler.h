/*! \file EventHandler.h
*
* This will handle all of the user interaction within the game.
*
*/

#pragma once

#include "defs.h"

class EventHandler
{
public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	EventHandler();

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~EventHandler();

	// Data Members 

private:

	sf::Event m_Event; 

	// Member Functions

public:

	//--------------------------------------------------------
	/*! \fn CheckForEvents : This will be used to process any events which happened during this loop. 
	*Param One : RenderWindow - This will be the current game window. 
	*/
	void m_CheckForEvents(sf::RenderWindow & window);
};