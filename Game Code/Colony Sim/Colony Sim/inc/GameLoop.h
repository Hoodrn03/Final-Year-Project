/*! \file Gameloop.h
*
* This class will contain the main gane loop and allow for the changing between game states.
* This will host the main functionality of the game. 
*
*/

#pragma once

#include "Window.h"
#include "EventHandler.h"
#include "UserInterface.h"
#include "FontManager.h"

#include "GameMap.h"
#include "ColonistManager.h"
#include "ResourceManagement.h"
#include "Mouse.h"

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

	/*! \var This will form the main user interface for the game. */
	UserInterface m_clUserInterface;

	/*! \var This will allow for the assignment of fonts for the game. */
	FontManager m_clFontManager;

	/*! \var This class will be used to manage the game map. */
	Map m_clMap;

	/*! \var This will manage all of the colonists within the game at any given time. */
	ColonistManager m_clColonistManager;

	/*! \var This will allow for ingame resources to be created and managed. */
	ResourceManagement m_clResourceManagement;

	/*! \var Controls mouse actions and functions for the game. */
	Mouse m_clMouse;

	/*! \var This is the games current frame rate. */
	int m_FrameRate = 0;

	/*! \var The current change in time since the last frame. */
	float m_fDeltaTime = 0;

	/*! \var This is the timer for the frame rate, it gets reset every second. */
	sf::Clock m_FrameRateCounter;

	/*! \var This timer will be used to update the current delta time. */
	sf::Clock m_DeltaTimer;

	/*! \var A second parallel thread, which will be used for pathfinding within the game. */
	std::thread l_First;

private:

	// Member Functions

public:

	//--------------------------------------------------------
	//						Main Menu
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn SetUp : This will be used at startup to initalize any data for the game.
	*
	*/
	int m_SetUp();

	//--------------------------------------------------------
	/*! \fn CreateExitButton : Used to create an exit button for the main menu. 
	*
	*/
	tgui::Button::Ptr m_CreateExitButton();

	//--------------------------------------------------------
	/*! \fn CreateBeginButton : Used to create a begin button for the main menu. 
	*
	*/
	tgui::Button::Ptr m_CreateBeginButton();

	//--------------------------------------------------------
	/*! \fn MainMenu : Used to open up the main menu for the game. 
	*
	*/
	int m_MainMenu();

	//--------------------------------------------------------
	/*! \fn RenderMainMenu : Used to draw all items onto the main menu. 
	*
	*/
	void m_RenderMainMenu();

	//--------------------------------------------------------
	//						Main Game
	//--------------------------------------------------------

	void m_BeginGame();

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
	void m_RenderGame();

	//--------------------------------------------------------
	//				Universal Functions 
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn CheckFramerate : Every frame This will check the current framerate of the game and output it.
	*
	*/
	void m_CheckFramerate(bool print);

	//--------------------------------------------------------
	/*! \fn Update Delta Time : This will update the current value of delta time; the time since the last frame.
	*
	*/
	void m_UpdateDeltaTime();

};