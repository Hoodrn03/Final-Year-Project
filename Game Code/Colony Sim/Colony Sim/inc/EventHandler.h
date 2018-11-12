/*! \file EventHandler.h
*
* This will handle all of the user interaction within the game.
*
*/

#pragma once

#include "defs.h"

/*! \class This will be used to handle all of the events within the game. */
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

	// Base Key Values. 

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

	/*! \var This will be used to move the view up if the appropriate key is pressed. */
	bool m_bMoveViewUp;

	/*! \var This will be used to move the view down if the appropriate key is pressed. */
	bool m_bMoveViewDown;

	/*! \var This will be used to move the view left if the appropriate key is pressed. */
	bool m_bMoveViewLeft; 

	/*! \var This will be used to move the view up if the appropriate key is pressed. */
	bool m_bMoveViewRight;

	/*! \var This will be the current state of the mouse wheel. */
	int m_iMouseWheelState = 0; 

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
	/*! \fn Check View Up Value : This will be used to check if the up key was pressed. 
	*
	*/
	bool m_CheckViewUpValue(); 

	//--------------------------------------------------------
	/*! \fn Check View Down Value : This will be used to check if the down key was pressed.
	*
	*/
	bool m_CheckViewDownValue();

	//--------------------------------------------------------
	/*! \fn Check View Left Value : This will be used to check if the left key was pressed.
	*
	*/
	bool m_CheckViewLeftValue(); 

	//--------------------------------------------------------
	/*! \fn Check View Right Value : This will be used to check if the right key was pressed.
	*
	*/
	bool m_CheckViewRightValue(); 

	//--------------------------------------------------------
	/*! \fn Check For Mouse Wheel : This will check to see if the mouse wheel has been moved. 
	*
	*/
	void m_CheckForMouseWheel(); 

	//--------------------------------------------------------
	/*! \fn Get Mouse Wheel State : This will be used to return the state of the mouse wheel. 
	*
	*/
	int & m_GetMouseWheelState(); 

	//--------------------------------------------------------
	/*! \fn Check for layer change : This will see if a layer chnage key was pressed. 
	*
	*/
	void m_CheckForLayerChange(); 

	//--------------------------------------------------------
	/*! \fn Current layer change value : Will return the layer change key value.
	*
	*/
	int & m_CurrentLayerChangeValue(); 
};