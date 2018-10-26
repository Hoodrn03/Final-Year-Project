/*! \file GameLoop.cpp
*
* This will hold all of the definitions for the class GameLoop.
*
*/

#include "GameLoop.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
Gameloop::Gameloop()
{
}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
Gameloop::~Gameloop()
{
}

//--------------------------------------------------------
/*! \fn SetUp : This will be used at startup to initalize any data for the game. 
*
*/
int Gameloop::m_SetUp()
{

	// Setup game items. 

	if (m_clWindow.m_InitWindow(500, 500, "Colony Sim") != 0)
	{
		return 1;
	}

	// Begin game. 

	m_Update(); 

	return 0; 

}

//--------------------------------------------------------
/*! \fn Update : This will house the game loop and be used to update any logic. 
*
*/
void Gameloop::m_Update()
{
	while (m_clWindow.m_GetWindow().isOpen())
	{

		m_clEventHandler.m_CheckForEvents(m_clWindow.m_GetWindow()); 

		m_Render(); 
	}

}

//--------------------------------------------------------
/*! \fn Render : This will be used to draw all of the objects into the window. 
*
*/
void Gameloop::m_Render()
{
	m_clWindow.m_GetWindow().clear();

	m_clWindow.m_GetWindow().display(); 
}
