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

void ColonistManager::m_Pathfinding(Grid & CurrentGrid, ResourceManagement & resourceManager, BuildingManager & buildingManager)
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
					WoodResource * l_TargetTree(resourceManager.m_FindClosestTree(v_clColonists[i].m_GetObjectPos()));

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

				// Find Nearest Building. 

				else if (v_clColonists[i].m_GetCurrentJob() == _CONSTRUCTION)
				{
					// Find a target building (clostest building). 
					BuildingObject * l_TargetBuild(buildingManager.m_GetClosestBuilding(v_clColonists[i].m_GetObjectPos()));

					if (l_TargetBuild == nullptr)
					{
						// If there is no object set to be built; find a random dirt cell to move to. 
						v_clColonists[i].m_iIdleCounter++;

						v_clColonists[i].m_FindNewPath(CurrentGrid.m_GetRandomDirtCell(v_clColonists[i].m_GetCurrentLayer()));

						// IF the colonist has not had a new building target for a few loops reset to idle. 
						if (v_clColonists[i].m_iIdleCounter >= 25)
						{
							v_clColonists[i].m_SetJob(_IDLE);
						}
					}
					else
					{
						// If a building has been found. 
						v_clColonists[i].m_AssignBuild(l_TargetBuild);

						// If the colonist is not at the building. 
						if (v_clColonists[i].m_AtTargetBuild() == false)
						{
							// Move the colonist to that building. 
							v_clColonists[i].m_FindNewPath(l_TargetBuild->m_GetCurrentCell());
						}
					}

				if (v_clColonists[i].m_iNeededWood > 0)
				{
					WoodPile * l_TargetPile = resourceManager.m_FindClosestWoodPile(v_clColonists[i].m_GetObjectPos());

					if (v_clColonists[i].m_iCurrentWood <= v_clColonists[i].m_iNeededWood)
					{
						std::cout << "Looking For Wood" << std::endl;

						if (v_clColonists[i].m_GetCurrentCell()->m_GetCellId() == l_TargetPile->m_GetCurentCell()->m_GetCellId())
						{
							v_clColonists[i].m_iCurrentWood += l_TargetPile->m_TakeWood(v_clColonists[i].m_iNeededWood);

							std::cout << "Colonist Current Wood : " << v_clColonists[i].m_iCurrentWood << std::endl;
						}
					}

					if (l_TargetPile == nullptr)
					{
						// If there is no object set to be built; find a random dirt cell to move to. 
						v_clColonists[i].m_iIdleCounter++;

						std::cout << "No Wood" << std::endl;

						v_clColonists[i].m_FindNewPath(CurrentGrid.m_GetRandomDirtCell(v_clColonists[i].m_GetCurrentLayer()));

						// IF the colonist has not had a new building target for a few loops reset to idle. 
						if (v_clColonists[i].m_iIdleCounter >= 25)
						{
							v_clColonists[i].m_SetJob(_IDLE);
						}
					}
					else
					{
						v_clColonists[i].m_FindNewPath(l_TargetPile->m_GetCurentCell());
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

void ColonistManager::m_SetColonistIdle()
{
	if (v_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < v_clColonists.size(); i++)
		{
			if (v_clColonists[i].m_GetSelectedValue() == true)
			{
				v_clColonists[i].m_SetJob(_IDLE);
			}
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

void ColonistManager::m_SetColonistConstruction()
{
	if (v_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < v_clColonists.size(); i++)
		{
			if (v_clColonists[i].m_GetSelectedValue() == true)
			{
				v_clColonists[i].m_SetJob(_CONSTRUCTION);
			}
		}
	}
}

void ColonistManager::m_CreateColonistActionButtons(sf::Font gameFont, sf::RenderWindow &window)
{

	// Init Button Sizes.

	int l_iButtonWidth = (int)(window.getSize().x * 0.15f);
	int l_iButtonHeight = (int)(window.getSize().y * 0.075f);

	// Init Button Position. 

	int l_iButtonX = 0;
	int l_iButtonY = window.getSize().y - l_iButtonHeight;

	// Clear Button Vector 

	v_ListOfButtons.clear();

	// Cut Trees Button. 

	tgui::Button::Ptr l_TempButton = tgui::Button::create();

	l_TempButton->setSize(l_iButtonWidth, l_iButtonHeight);
	l_TempButton->setPosition(l_iButtonX, l_iButtonY);
	l_TempButton->setInheritedFont(gameFont);
	l_TempButton->setText("Cut Trees");
	l_TempButton->setTextSize(0);
	// Use a lambda function to add a small operation to the button when it is pressed. 
	l_TempButton->connect("Pressed", [&]() {  m_SetColonistTreeCut(); });

	v_ListOfButtons.push_back(l_TempButton);

	// Construction Button. 

	l_iButtonX += l_iButtonWidth; 

	l_TempButton = tgui::Button::create();

	l_TempButton->setSize(l_iButtonWidth, l_iButtonHeight);
	l_TempButton->setPosition(l_iButtonX, l_iButtonY);
	l_TempButton->setInheritedFont(gameFont);
	l_TempButton->setText("Construction");
	l_TempButton->setTextSize(0);
	l_TempButton->connect("Pressed", [&]() { m_SetColonistConstruction();  });

	v_ListOfButtons.push_back(l_TempButton);

	// Idle Button.

	l_iButtonX += l_iButtonWidth;

	l_TempButton = tgui::Button::create();

	l_TempButton->setSize(l_iButtonWidth, l_iButtonHeight);
	l_TempButton->setPosition(l_iButtonX, l_iButtonY);
	l_TempButton->setInheritedFont(gameFont);
	l_TempButton->setText("Idle");
	l_TempButton->setTextSize(0);
	l_TempButton->connect("Pressed", [&]() { m_SetColonistIdle();  });

	v_ListOfButtons.push_back(l_TempButton);

	// Temp.

	l_iButtonX += l_iButtonWidth;

	l_TempButton = tgui::Button::create();

	l_TempButton->setSize(l_iButtonWidth, l_iButtonHeight);
	l_TempButton->setPosition(l_iButtonX, l_iButtonY);
	l_TempButton->setInheritedFont(gameFont);
	l_TempButton->setText("Placeholder");
	l_TempButton->setTextSize(0);
	l_TempButton->connect("Pressed", [&]() {});

	v_ListOfButtons.push_back(l_TempButton);
}

std::vector<tgui::Button::Ptr> ColonistManager::m_GetColonistButtons()
{
	return v_ListOfButtons;
}
