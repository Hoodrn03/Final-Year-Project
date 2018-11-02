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

	/*! \var Key to move the view up. */
	sf::Keyboard::Key m_ViewUp = sf::Keyboard::W;

	/*! \var Key to move the view down. */
	sf::Keyboard::Key m_ViewDown = sf::Keyboard::S; 

	/*! \var Key to move the view left. */
	sf::Keyboard::Key m_ViewLeft = sf::Keyboard::A;

	/*! \var Key to move the view right. */
	sf::Keyboard::Key m_ViewRight = sf::Keyboard::D; 

	/*! \var Key to change the layer up. */
	sf::Keyboard::Key m_LayerUp = sf::Keyboard::PageUp;

	/*! \var Key to change the layer down. */
	sf::Keyboard::Key m_LayerDown = sf::Keyboard::PageDown; 

	/*! \var Which movement key was pressed for the view to move. */
	int m_iViewMoveValue = 0; 

	/*! \var Which key was pressed for the layer to change. */
	int m_iLayerMoveValue = 0; 

	// Member Functions

public:

	//--------------------------------------------------------
	/*! \fn CheckForEvents : This will be used to process any events which happened during this loop. 
	*Param One : RenderWindow - This will be the current game window. 
	*/
	void m_CheckForEvents(sf::RenderWindow & window);

	//--------------------------------------------------------
	/*! \fn Check for view move keys : This will be used to see if a movement key was pressed this frame. 
	*
	*/
	void m_CheckForViewMoveKeys(); 

	//--------------------------------------------------------
	/*! \fn Check for layer change : This will see if a layer chnage key was pressed. 
	*
	*/
	void m_CheckForLayerChange(); 

	//--------------------------------------------------------
	/*! \fn Check view move value : Will return the current movemnt key value. 
	*
	*/
	int m_CurentViewMoveValue(); 

	//--------------------------------------------------------
	/*! \fn Current layer change value : Will return the layer change key value.
	*
	*/
	int & m_CurrentLayerChangeValue(); 
};