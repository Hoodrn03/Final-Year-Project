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
#include "ColonistManager.h"
#include "ResourceManagement.h"

/*! \class This will hold the main game loop, it will have three main functions; setup, update and render. */
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

	/*! \var This class will be used to manage the game map. */
	Map m_clMap; 

	/*! \var This will manage all of the colonists within the game at any given time. */
	ColonistManager m_clColonistManager; 

	ResourceManagement m_clResourceManagement; 

	/*! \var This is the games current frame rate. */
	int m_FrameRate = 0;

	/*! \var The current change in time since the last frame. */
	float m_fDeltaTime = 0; 

	/*! \var This is the timer for the frame rate, it gets reset every second. */
	sf::Clock m_FrameRateCounter; 

	/*! \var This timer will be used to update the current delta time. */
	sf::Clock m_DeltaTimer; 

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
	/*! \fn Update Pathfinding : This will be used to update all of the pathfinding elements in the game. 
	*
	*/
	void m_UpdatePathfinding(); 

	//--------------------------------------------------------
	/*! \fn Draw Filter : This will be used to limit what is drawn to only those within the game view. 
	*
	*/
	void m_DrawFilter(); 

	//--------------------------------------------------------
	/*! \fn Render : This will be used to draw all of the objects into the window.
	*
	*/
	void m_Render();

	//--------------------------------------------------------
	/*! \fn CheckFramerate : Every frame this will check the current framerate of the game and output it. 
	*
	*/
	void m_CheckFramerate(); 

	//--------------------------------------------------------
	/*! \fn Update Delta Time : This will update the current value of delta time; the time since the last frame. 
	*
	*/
	void m_UpdateDeltaTime(); 

};