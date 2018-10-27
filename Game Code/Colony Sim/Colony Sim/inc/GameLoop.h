/*! \file Gameloop.h
*
* This class will contain the main gane loop and allow for the changing between game states.
* This will host the main functionality of the game. 
*
*/

#pragma once

#include "Window.h"
#include "EventHandler.h"

#include "GameMap.h"

class Gameloop
{

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Gameloop();

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~Gameloop();

	// Data Members 

	/*! \var This Class will control the game window. */
	Window m_clWindow;

	/*! \var This Class will handle all of the events within the game. */
	EventHandler m_clEventHandler; 

	Map m_clMap; 

	sf::RectangleShape tempShape; 

private:

	// Member Functions

public:

	//--------------------------------------------------------
	/*! \fn SetUp : This will be used at startup to initalize any data for the game.
	*
	*/
	int m_SetUp();

	//--------------------------------------------------------
	/*! \fn Update : This will house the game loop and be used to update any logic.
	*
	*/
	void m_Update(); 

	//--------------------------------------------------------
	/*! \fn Render : This will be used to draw all of the objects into the window.
	*
	*/
	void m_Render();


};