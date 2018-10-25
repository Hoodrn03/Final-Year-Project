/*! \file GameLoop.cpp
*
* This will hold all of the definitions for the class window.
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

int Gameloop::m_SetUp()
{
	if (m_clWindow.m_InitWindow(500, 500, "Colony Sim") != 0)
	{
		return 1;
	}

	return 0; 

}

void Gameloop::m_Update()
{
	while (m_clWindow.m_GetWindow().isOpen())
	{

		m_clEventHandler.m_CheckForEvents(m_clWindow.m_GetWindow()); 

		m_Render(); 
	}

}

void Gameloop::m_Render()
{
	m_clWindow.m_GetWindow().clear();

	m_clWindow.m_GetWindow().display(); 
}
