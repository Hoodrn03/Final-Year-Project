/*! \file ColonistManager.cpp
*
* This will hold all of the definitions for the class ColonistManager.
*
*/

#include "../inc/ColonistManager.h"

void m_Print(std::string text)
{
	std::cout << text << std::endl;
}

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
void ColonistManager::m_Pathfinding(Grid & CurrentGrid, ResourceManagement & currentManager)
{
	if (v_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < v_clColonists.size(); i++)
		{

			if (v_clColonists[i].m_GetFindNewPath() == true)
			{
				// This will allow for pathfinding when colonist is idle. 
				if (v_clColonists[i].m_GetCurrentJob() == _IDLE)
				{
					if (v_clColonists[i].m_iIdleCounter > 0)
					{
						v_clColonists[i].m_iIdleCounter = 0; 
					}

					v_clColonists[i].m_FindNewPath(CurrentGrid.m_GetRandomDirtCell(v_clColonists[i].m_GetCurrentLayer()));
				}

				// This will allow for pathfinding when colonist is logging. 
				else if (v_clColonists[i].m_GetCurrentJob() == _LOGGING)
				{
					// Find a target tree (clostest tree). 
					WoodResource * l_TargetTree(currentManager.m_FindClosestTree(v_clColonists[i].m_GetObjectPos()));

					if (l_TargetTree == nullptr)
					{
						// If there is no tree set to be cut; find a random dirt cell to move to. 
						v_clColonists[i].m_iIdleCounter++; 

						v_clColonists[i].m_FindNewPath(CurrentGrid.m_GetRandomDirtCell(v_clColonists[i].m_GetCurrentLayer()));

						// IF the colonist has not had a new cutting target for a few loops reset to idle. 
						if (v_clColonists[i].m_iIdleCounter >= 25)
						{
							v_clColonists[i].m_SetJob(_IDLE);
						}
					}
					else
					{
						// If a tree has been found. 
						v_clColonists[i].m_AssignTree(l_TargetTree);

						// If the colonist is not at the tree. 
						if (v_clColonists[i].m_AtTargetTree() == false)
						{
							// Move the colonist to that tree. 
							v_clColonists[i].m_FindNewPath(l_TargetTree->m_GetCurrentCell());
						}
					}
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

			if (mouseDown)
			{
				v_clColonists[i].m_SelectColonist(false);
			}

		}
	}
}

void ColonistManager::m_CheckForSelected()
{
	int l_iCount = 0; 

	if (v_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < v_clColonists.size(); i++)
		{
			if (v_clColonists[i].m_GetSelectedValue() == true)
			{
				m_bColonistSelected = true; 
			}
			else
			{
				l_iCount++;
			}
		}

		if (l_iCount == v_clColonists.size())
		{
			m_bColonistSelected = false; 
		}
	}
}

void ColonistManager::m_SetColonistTreeCut()
{
	if (v_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < v_clColonists.size(); i++)
		{
			if (v_clColonists[i].m_GetSelectedValue() == true)
			{
				v_clColonists[i].m_SetJob(_LOGGING); 
			}
		}
	}
}

void ColonistManager::m_CreateColonistActionButtons(sf::Font gameFont, sf::RenderWindow &window)
{
	tgui::Button::Ptr l_CutTreeButton = tgui::Button::create();

	l_CutTreeButton->setSize(window.getSize().x * 0.15f, window.getSize().y * 0.10f);

	l_CutTreeButton->setPosition(0, window.getSize().y - l_CutTreeButton->getSize().y);

	l_CutTreeButton->setInheritedFont(gameFont);

	l_CutTreeButton->setText("Cut Trees");

	l_CutTreeButton->connect("pressed", [&]() { m_SetColonistTreeCut(); });

	v_ListOfButtons.push_back(l_CutTreeButton);
}

std::vector<tgui::Button::Ptr> ColonistManager::m_GetColonistButtons()
{
	return v_ListOfButtons;
}
