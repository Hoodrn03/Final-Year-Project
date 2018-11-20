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

	// Generate a new seed for the program. 

	std::srand((unsigned int)time(0)); 

	// Setup game items. 

	if (m_clWindow.m_InitWindow(800, 800, "Colony Sim") != 0)
	{
		return 1;
	}

	m_clMap.m_SetUpGameMap(sf::Vector2f(800, 800), sf::Vector2f(0, 0)); 

	m_clWindow.m_GetWindow().setKeyRepeatEnabled(false);

	m_clWindow.m_GetWindow().setFramerateLimit(60);

	int l_iNumberOfColonists = 1; 

	for (int i = 0; i < l_iNumberOfColonists; i++)
	{
		Colonist l_clColonist;

		l_clColonist.m_CreateColonistBody(sf::Vector2f(5, 5), m_clMap.m_GetGrid().m_GetRandomDirtCell(m_clMap.m_GetGroundLevel()));

		m_clColonistList.push_back(l_clColonist);
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

		m_CheckFramerate(); 

		m_UpdateDeltaTime(); 

		// Handle Events. 
		m_clEventHandler.m_CheckForEvents(m_clWindow.m_GetWindow()); 

		m_clWindow.m_CheckForViewMove(m_clEventHandler.m_CheckViewUpValue(), m_clEventHandler.m_CheckViewDownValue(), m_clEventHandler.m_CheckViewLeftValue(), m_clEventHandler.m_CheckViewRightValue()); 

		m_clWindow.m_CheckForViewScroll(m_clEventHandler.m_GetMouseWheelState());

		m_clMap.m_CheckForLayerChange(m_clEventHandler.m_CurrentLayerChangeValue());

		m_clMap.m_Update(); 

		if (m_clColonistList.size() > 0)
		{
			for (unsigned int i = 0; i < m_clColonistList.size(); i++)
			{
				if (m_clColonistList[i].m_GetFindNewPath() == true)
				{
					 m_clColonistList[i].m_FindNewPath(m_clMap.m_GetGrid().m_GetRandomDirtCell(m_clMap.m_GetGroundLevel()));
				}

				m_clColonistList[i].m_Update();
			}
		}

		// Draw Items. 
		m_Render(); 
	}

}

//--------------------------------------------------------
/*! \fn Draw Filter : This will be used to limit what is drawn to only those within the game view.
*
*/
void Gameloop::m_DrawFilter()
{
	m_clMap.m_DrawFilter(m_clWindow.m_GetViewUpperBounds(), m_clWindow.m_GetViewLowerBounds());

	if (m_clColonistList.size() > 0)
	{
		for (unsigned int i = 0; i < m_clColonistList.size(); i++)
		{
			m_clColonistList[i].m_DrawFilter(m_clWindow.m_GetViewUpperBounds(), m_clWindow.m_GetViewLowerBounds());
		}
	}
}

//--------------------------------------------------------
/*! \fn Render : This will be used to draw all of the objects into the window. 
*
*/
void Gameloop::m_Render()
{
	// Check items for drawing. 

	m_DrawFilter(); 

	m_clWindow.m_GetWindow().clear();

	// Todo: Add items to draw. 

	m_clMap.m_DrawGameObject(m_clWindow.m_GetWindow()); 

	if (m_clColonistList.size() > 0)
	{
		for (unsigned int i = 0; i < m_clColonistList.size(); i++)
		{
			m_clColonistList[i].m_DrawGameObject(m_clWindow.m_GetWindow());
		}
	}
	m_clWindow.m_GetWindow().display(); 
}

//--------------------------------------------------------
/*! \fn CheckFramerate : Every frame this will check the current framerate of the game and output it.
*
*/
void Gameloop::m_CheckFramerate()
{
	m_FrameRate++;

	if (m_FrameRateCounter.getElapsedTime().asSeconds() >= 1)
	{
		m_FrameRateCounter.restart(); 

		m_FrameRate = 0; 
	}
}

//--------------------------------------------------------
/*! \fn Update Delta Time : This will update the current value of delta time; the time since the last frame.
*
*/
void Gameloop::m_UpdateDeltaTime()
{
	m_fDeltaTime = m_DeltaTimer.restart().asSeconds();
}

