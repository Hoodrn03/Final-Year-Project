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

	/*! \var This will be used to detect an event within the game. */
	sf::Event m_Event; 

	sf::Keyboard::Key m_ViewUp = sf::Keyboard::W;
	sf::Keyboard::Key m_ViewDown = sf::Keyboard::S; 

	sf::Keyboard::Key m_ViewLeft = sf::Keyboard::A;
	sf::Keyboard::Key m_ViewRight = sf::Keyboard::D; 

	int m_iViewMoveValue = 0; 

	// Member Functions

public:

	//--------------------------------------------------------
	/*! \fn CheckForEvents : This will be used to process any events which happened during this loop. 
	*Param One : RenderWindow - This will be the current game window. 
	*/
	void m_CheckForEvents(sf::RenderWindow & window);

	void m_CheckForViewMoveKeys(); 

	int m_CurentViewMoveValue(); 
};