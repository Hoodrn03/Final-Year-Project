/*! \file ColonistManager.cpp
*
* This will hold all of the definitions for the class ColonistManager.
*
*/

#include "../inc/ColonistManager.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
ColonistManager::ColonistManager()
{
}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
ColonistManager::~ColonistManager()
{
}

//--------------------------------------------------------
/*! \fn Add Colonist : This will be used to add a new colonist into the vector.
*Param One : int - This will be the total number of colonists which should be added to the game.
*Param Two : Vector2f - The dimentions for the colonists (height and width).
*Param Three : Grid - The grid which is overlayed onto the current game map.
*Param Four : int - The layer which the colonists should be spawend onto.
*/
void ColonistManager::m_AddColonist(int numberOfColonists, sf::Vector2f dimentions, Grid & currentGrid, int startingLayer)
{
	int l_iNumberOfColonists = numberOfColonists;

	for (int i = 0; i < l_iNumberOfColonists; i++)
	{
		Colonist l_clColonist;

		if(l_clColonist.m_CreateColonistBody(sf::Vector2f(5, 5), currentGrid.m_GetRandomDirtCell(startingLayer)) == 0)
		{
			v_clColonists.push_back(l_clColonist);
		}
		else 
		{
			i--; 
		}
	}
}

//--------------------------------------------------------
/*! \fn Update : This will update the logic for all of the colonists.
*Param One : Grid - the current grid which is overlayed onto the game map.
*/
void ColonistManager::m_Update(Grid & CurrentGrid)
{
	if (v_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < v_clColonists.size(); i++)
		{
			v_clColonists[i].m_Update(); 

			v_clColonists[i].m_UpdateCurrentCell(CurrentGrid.m_ConvertWorldPosToGridPos(v_clColonists[i].m_GetObjectPos(), v_clColonists[i].m_GetCurrentLayer()));
		}
	}

}

//--------------------------------------------------------
/*! \fn Pathfinding : This will be used to manage the colonist's current path.
*Param One : Grid - the current grid which is overlayed onto the game map.
*/
void ColonistManager::m_Pathfinding(Grid & CurrentGrid)
{
	if (v_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < v_clColonists.size(); i++)
		{
			if (v_clColonists[i].m_GetFindNewPath() == true)
			{
				if (v_clColonists[i].m_GetCurrentJob() == _IDLE)
				{
					v_clColonists[i].m_FindNewPath(CurrentGrid.m_GetRandomDirtCell(v_clColonists[i].m_GetCurrentLayer()));
				}
			}
		}
	}
}

//--------------------------------------------------------
/*! \fn Render : This will draw all of the colonists onto the game window.
*Param One : RenderWindow : The current game window.
*/
void ColonistManager::m_Render(sf::RenderWindow & window)
{
	if (v_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < v_clColonists.size(); i++)
		{
			v_clColonists[i].m_DrawGameObject(window);
		}
	}
}

//--------------------------------------------------------
/*! \fn Draw Filter : This will be used to limit if the colonists are drawn or not.
*Param One : Vector2f - The top left of the game view.
*Param Two : Vector2f - The bottom right of the game view.
*/
void ColonistManager::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
	if (v_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < v_clColonists.size(); i++)
		{
			v_clColonists[i].m_DrawFilter(topLeft, bottomRight);
		}
	}
}

//--------------------------------------------------------
/*! \fn Draw Filter (Overload) : This will be used to limit if the colonists are drawn or not.
*Param One : Vector2f - The top left of the game view.
*Param Two : Vector2f - The bottom right of the game view.
*Param Three : unsinged int : The current layer the window is displaying.
*/
void ColonistManager::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, unsigned int currentLayer)
{
	if (v_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < v_clColonists.size(); i++)
		{
			v_clColonists[i].m_DrawFilter(topLeft, bottomRight, currentLayer);
		}
	}
}

void ColonistManager::m_SelectColonist(sf::Vector2f topLeft, sf::Vector2f bottomRight, bool mouseDown)
{
	if (v_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < v_clColonists.size(); i++)
		{
			if (mouseDown)
			{
				if ((v_clColonists[i].m_GetObjectPos().x > topLeft.x && v_clColonists[i].m_GetObjectPos().x < bottomRight.x) &&
					(v_clColonists[i].m_GetObjectPos().y > topLeft.y && v_clColonists[i].m_GetObjectPos().y < bottomRight.y))
				{
					v_clColonists[i].m_SelectColonist(true);
				}

				else if ((v_clColonists[i].m_GetObjectPos().x < topLeft.x && v_clColonists[i].m_GetObjectPos().x > bottomRight.x) &&
					(v_clColonists[i].m_GetObjectPos().y < topLeft.y && v_clColonists[i].m_GetObjectPos().y > bottomRight.y))
				{
					v_clColonists[i].m_SelectColonist(true);
				}

				else
				{
					v_clColonists[i].m_SelectColonist(false);
				}
			}
		}
	}
}
