/*! \file GameLoop.cpp
*
* This will hold all of the definitions for the class GameLoop.
*
*/

#include "../inc/GameLoop.h"

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

	if (m_clWindow.m_InitWindow(800, 800, "Colony Sim") != 0)
	{
		return 1;
	}

	m_clMap.m_SetUpGameMap(sf::Vector2f(1600, 1600), sf::Vector2f(0, 0)); 

	tempShape.setSize(sf::Vector2f(50.f, 50.f)); 

	tempShape.setPosition(100.f, 100.f); 

	tempShape.setFillColor(sf::Color::Blue); 

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

		// Handle Events. 
		m_clEventHandler.m_CheckForEvents(m_clWindow.m_GetWindow()); 

		m_clWindow.m_CheckForViewMove(m_clEventHandler.m_CurentViewMoveValue()); 

		// Draw Items. 
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

	// Todo: Add items to draw. 

	m_clMap.m_DrawGameObject(m_clWindow.m_GetWindow()); 

	m_clWindow.m_GetWindow().draw(tempShape); 

	m_clWindow.m_GetWindow().display(); 
}
