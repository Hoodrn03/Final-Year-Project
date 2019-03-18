/*! \file This will hold the class definitions for the class ResourceManagement */

#include "..\inc\ResourceManagement.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
ResourceManagement::ResourceManagement()
{
}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
ResourceManagement::~ResourceManagement()
{
}

void ResourceManagement::m_AssignFont(sf::Font mainFont)
{
	m_LocalFont = mainFont; 
}

//--------------------------------------------------------
/*! \fn AddTrees : This will be used to add a number of trees into the game.
*Param One : int - The number of trees to add.
*Param Two : float - The maximum radius for the spawned trees.
*Param Three : int - The layer to spawn the trees.
*Param Four : Grid - The grid reference to spawn the trees onto.
*/
void ResourceManagement::m_AddTrees(int numberOfTrees, float maxRadius, int layer, Grid & grid)
{
	for (int i = 0; i < numberOfTrees; i++)
	{
		WoodResource l_TempTree; 

		Cells * l_TempCell = grid.m_GetRandomDirtCell(layer);

		l_TempTree.m_CreateTree(maxRadius, l_TempCell->m_GetCellCentre(), layer, l_TempCell); 

		v_clTrees.push_back(l_TempTree);
	}

}

void ResourceManagement::m_AddWoodPile(WoodResource * cutTree)
{
	WoodPile  l_TempPile; 

	l_TempPile.m_InitWoodPile(cutTree->m_GetCurrentCell(), m_LocalFont, cutTree->m_GetCurrentGrowth()); 

	v_clWoodPiles.push_back(l_TempPile); 
}

//--------------------------------------------------------
/*! \fn DrawTrees : Draws the trees into the game.
*Param One : RenderWindow - The main game window.
*/
void ResourceManagement::m_DrawTrees(sf::RenderWindow & window)
{
	if (v_clTrees.size() > 0)
	{
		for (unsigned int i = 0; i < v_clTrees.size(); i++)
		{
			v_clTrees[i].m_DrawGameObject(window); 
		}
	}
}

void ResourceManagement::m_DrawWoodPiles(sf::RenderWindow & window)
{
	if (v_clWoodPiles.size() > 0)
	{
		for (unsigned int i = 0; i < v_clWoodPiles.size(); i++)
		{
			v_clWoodPiles[i].m_DrawGameObject(window);
		}
	}
}

//--------------------------------------------------------
/*! \fn DrawFilter : Used to limit the game objects from being drawn.
*Param One : Vector2f - The top left of the game's view.
*Param Two : Vector2f - The bottom right of the game's view.
*/
void ResourceManagement::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
	if (v_clTrees.size() > 0)
	{
		for (unsigned int i = 0; i < v_clTrees.size(); i++)
		{
			v_clTrees[i].m_DrawFilter(topLeft, bottomRight); 
		}
	}

	if (v_clWoodPiles.size() > 0)
	{
		for (unsigned int i = 0; i < v_clWoodPiles.size(); i++)
		{
			v_clWoodPiles[i].m_DrawFilter(topLeft, bottomRight);
		}
	}
}

//--------------------------------------------------------
/*! \fn DrawFilter : Used to limit the game objects from being drawn.
*Param One : Vector2f - The top left of the game's view.
*Param Two : Vector2f - The bottom right of the game's view.
*Param Three : int - The current layer the player is on.
*/
void ResourceManagement::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, int currentLayer)
{
	if (v_clTrees.size() > 0)
	{
		for (unsigned int i = 0; i < v_clTrees.size(); i++)
		{
			v_clTrees[i].m_DrawFilter(topLeft, bottomRight, currentLayer);
		}
	}

	if (v_clWoodPiles.size() > 0)
	{
		for (unsigned int i = 0; i < v_clWoodPiles.size(); i++)
		{
			v_clWoodPiles[i].m_DrawFilter(topLeft, bottomRight, currentLayer);
		}
	}
}

//--------------------------------------------------------
/*! \fn Update : Update the current game resources.
*
*/
void ResourceManagement::m_Update()
{
	if (v_clTrees.size() > 0)
	{
		for (unsigned int i = 0; i < v_clTrees.size(); i++)
		{
			v_clTrees[i].m_Update();
		}
	}
}

void ResourceManagement::m_AssignAction(currentAction newAction)
{
	m_CurretAction = newAction; 
}

void ResourceManagement::m_SelectResources(sf::Vector2f m_TopLeft, sf::Vector2f bottomRight)
{
	switch (m_CurretAction)
	{

		// Cut Down Selected Trees. 
	case _CUT_TREES:

		if (v_clTrees.size() > 0)
		{
			for (unsigned int i = 0; i < v_clTrees.size(); i++)
			{
				// Check each configuration of the selection box. 

				if ((v_clTrees[i].m_GetObjectPos().x > m_TopLeft.x && v_clTrees[i].m_GetObjectPos().x < bottomRight.x) &&
					(v_clTrees[i].m_GetObjectPos().y > m_TopLeft.y && v_clTrees[i].m_GetObjectPos().y < bottomRight.y))
				{
					v_clTrees[i].m_SetTreeCutDown(); 
				}

				if ((v_clTrees[i].m_GetObjectPos().x < m_TopLeft.x && v_clTrees[i].m_GetObjectPos().x > bottomRight.x) &&
					(v_clTrees[i].m_GetObjectPos().y < m_TopLeft.y && v_clTrees[i].m_GetObjectPos().y > bottomRight.y))
				{
					v_clTrees[i].m_SetTreeCutDown();
				}
			}
		}

		break;

		// Cancel All commands in selected area. 
	default:

		if (v_clTrees.size() > 0)
		{
			for (unsigned int i = 0; i < v_clTrees.size(); i++)
			{
				// Check each configuration of the selection box. 

				if ((v_clTrees[i].m_GetObjectPos().x > m_TopLeft.x && v_clTrees[i].m_GetObjectPos().x < bottomRight.x) &&
					(v_clTrees[i].m_GetObjectPos().y > m_TopLeft.y && v_clTrees[i].m_GetObjectPos().y < bottomRight.y))
				{
					v_clTrees[i].m_CancelTreeCutDown();
				}

				if ((v_clTrees[i].m_GetObjectPos().x < m_TopLeft.x && v_clTrees[i].m_GetObjectPos().x > bottomRight.x) &&
					(v_clTrees[i].m_GetObjectPos().y < m_TopLeft.y && v_clTrees[i].m_GetObjectPos().y > bottomRight.y))
				{
					v_clTrees[i].m_CancelTreeCutDown();
				}
			}
		}

		break;
	}

}

WoodResource * ResourceManagement::m_FindClosestTree(sf::Vector2f otherObject)
{

	// Var setup

	WoodResource * l_TempTree = nullptr;

	bool l_FirstTree = true; 

	float l_PrevXDist, l_PrevYDist;

	float l_XDist, l_YDist;

	if (v_clTrees.size() > 0)
	{
		for (unsigned int i = 1; i < v_clTrees.size(); i++)
		{
			// Ensure this only loops through trees chosen to be cut down. 

			if (v_clTrees[i].m_GetTreeCutDown() == true)
			{
				if (l_FirstTree == true)
				{
					// Find the first tree in the vector to begin the distance evaluations.

					l_TempTree = &v_clTrees[i]; 

					l_FirstTree = false;

					// Calculate the initial distance between the chosen object and the first tree. 

					if (v_clTrees[i].m_GetObjectPos().x > otherObject.x)
					{
						l_PrevXDist = v_clTrees[i].m_GetObjectPos().x - otherObject.x;
					}
					else
					{
						l_PrevXDist = otherObject.x - v_clTrees[i].m_GetObjectPos().x;
					}

					if (v_clTrees[i].m_GetObjectPos().y > otherObject.y)
					{
						l_PrevYDist = v_clTrees[i].m_GetObjectPos().y - otherObject.y;
					}
					else
					{
						l_PrevYDist = otherObject.y - v_clTrees[i].m_GetObjectPos().y;
					}
				}

				// Calculate the distance for the next tree. 

				if (v_clTrees[i].m_GetObjectPos().x > otherObject.x)
				{
					l_XDist = v_clTrees[i].m_GetObjectPos().x - otherObject.x;
				}
				else
				{
					l_XDist = otherObject.x - v_clTrees[i].m_GetObjectPos().x;
				}

				if (v_clTrees[i].m_GetObjectPos().y > otherObject.y)
				{
					l_YDist = v_clTrees[i].m_GetObjectPos().y - otherObject.y;
				}
				else
				{
					l_YDist = otherObject.y - v_clTrees[i].m_GetObjectPos().y;
				}

				// See if the new distance is shorter than the preveous one. 

				if ((l_XDist <= l_PrevXDist) && (l_YDist <= l_PrevYDist))
				{
					l_TempTree = &v_clTrees[i];

					l_PrevXDist = l_XDist;
					l_PrevYDist = l_YDist;
				}
			}
		}
	}

	if (l_TempTree == nullptr)
	{
		std::cout << "Unable to find tree" << std::endl;
	}

	return l_TempTree;
}

WoodPile * ResourceManagement::m_FindClosestWoodPile(sf::Vector2f otherObject)
{
	// Var setup

	WoodPile * l_TempWood = nullptr;

	bool l_FirstPile = true;

	float l_PrevXDist, l_PrevYDist;

	float l_XDist, l_YDist;

	if (v_clWoodPiles.size() > 0)
	{
		for (unsigned int i = 1; i < v_clWoodPiles.size(); i++)
		{
			if (l_FirstPile == true)
			{
				// Find the first tree in the vector to begin the distance evaluations.

				l_TempWood = &v_clWoodPiles[i];

				l_FirstPile = false;

				// Calculate the initial distance between the chosen object and the first tree. 

				if (v_clWoodPiles[i].m_GetObjectPos().x > otherObject.x)
				{
					l_PrevXDist = v_clWoodPiles[i].m_GetObjectPos().x - otherObject.x;
				}
				else
				{
					l_PrevXDist = otherObject.x - v_clWoodPiles[i].m_GetObjectPos().x;
				}

				if (v_clWoodPiles[i].m_GetObjectPos().y > otherObject.y)
				{
					l_PrevYDist = v_clWoodPiles[i].m_GetObjectPos().y - otherObject.y;
				}
				else
				{
					l_PrevYDist = otherObject.y - v_clWoodPiles[i].m_GetObjectPos().y;
				}
			}

			// Calculate the distance for the next tree. 

			if (v_clTrees[i].m_GetObjectPos().x > otherObject.x)
			{
				l_XDist = v_clTrees[i].m_GetObjectPos().x - otherObject.x;
			}
			else
			{
				l_XDist = otherObject.x - v_clTrees[i].m_GetObjectPos().x;
			}

			if (v_clTrees[i].m_GetObjectPos().y > otherObject.y)
			{
				l_YDist = v_clTrees[i].m_GetObjectPos().y - otherObject.y;
			}
			else
			{
				l_YDist = otherObject.y - v_clTrees[i].m_GetObjectPos().y;
			}

			// See if the new distance is shorter than the preveous one. 

			if ((l_XDist <= l_PrevXDist) && (l_YDist <= l_PrevYDist))
			{
				l_TempWood = &v_clWoodPiles[i];

				l_PrevXDist = l_XDist;
				l_PrevYDist = l_YDist;
			}

		}
	}

	if (l_TempWood == nullptr)
	{
		std::cout << "Unable to find Wood" << std::endl;
	}

	return l_TempWood;
}

void ResourceManagement::m_DeleteTrees()
{
	if (v_clTrees.size() > 0)
	{
		for (unsigned int i = 0; i < v_clTrees.size(); i++)
		{
			if (v_clTrees[i].m_GetMarkForDeletion() == true)
			{
				m_AddWoodPile(&v_clTrees[i]); 

				v_clTrees.erase(v_clTrees.begin() + i);  
			}
		}
	}

	if (v_clWoodPiles.size() > 0)
	{
		for (unsigned int i = 0; i < v_clWoodPiles.size(); i++)
		{
			if (v_clWoodPiles[i].m_GetMarkForDeletion() == true)
			{
				v_clWoodPiles.erase(v_clWoodPiles.begin() + i);
			}
		}
	}
}

void ResourceManagement::m_CreateActionButtons(float windowWidth, float windowHeight)
{
	// Init Button Sizes.

	int l_iButtonWidth = (int)(windowWidth * 0.15f);
	int l_iButtonHeight = (int)(windowHeight * 0.075f);

	// Create Buttons

	m_ActionButton = tgui::Button::create();

	m_ActionButton->setSize(l_iButtonWidth, l_iButtonHeight);
	m_ActionButton->setPosition(0, 0); 
	m_ActionButton->setInheritedFont(m_LocalFont); 
	m_ActionButton->setText("Actions"); 
	m_ActionButton->setTextSize(0);
	m_ActionButton->connect("Pressed", [&]() { m_DrawActionButtons(); });

	// Init Button Position. 

	int l_iButtonX = 0;
	int l_iButtonY = 0 + l_iButtonHeight;

	// Clear Button Vector 

	v_ActionButtons.clear(); 

	// Cancel Action Button. 

	tgui::Button::Ptr l_TempButton = tgui::Button::create(); 

	l_TempButton->setSize(l_iButtonWidth, l_iButtonHeight);
	l_TempButton->setPosition(l_iButtonX, l_iButtonY);
	l_TempButton->setInheritedFont(m_LocalFont);
	l_TempButton->setText("Cancel Actions");
	l_TempButton->setTextSize(0);
	// Use a lambda function to add a small operation to the button when it is pressed. 
	l_TempButton->connect("Pressed", [&]() { m_AssignAction(_NULL); });

	v_ActionButtons.push_back(l_TempButton);

	// Tree Cutting Button. 

	l_TempButton = tgui::Button::create();

	l_TempButton->setSize(l_iButtonWidth, l_iButtonHeight);
	l_TempButton->setPosition(l_iButtonX + l_iButtonWidth, l_iButtonY);
	l_TempButton->setInheritedFont(m_LocalFont);
	l_TempButton->setText("Cut Trees");
	l_TempButton->setTextSize(0);
	l_TempButton->connect("Pressed", [&]() { m_AssignAction(_CUT_TREES); });

	v_ActionButtons.push_back(l_TempButton);

	// Temp.

	l_TempButton = tgui::Button::create();

	l_TempButton->setSize(l_iButtonWidth, l_iButtonHeight);
	l_TempButton->setPosition(l_iButtonX + (l_iButtonWidth * 2), l_iButtonY);
	l_TempButton->setInheritedFont(m_LocalFont);
	l_TempButton->setText("Placeholder");
	l_TempButton->setTextSize(0);
	l_TempButton->connect("Pressed", [&]() { m_AssignAction(_CUT_TREES); });

	v_ActionButtons.push_back(l_TempButton);

}

void ResourceManagement::m_DrawActionButtons()
{
	m_bDisplayButtons = !m_bDisplayButtons;
}

std::vector<tgui::Button::Ptr> ResourceManagement::m_GetActionButtons()
{
	m_bButtonsCreated = !m_bButtonsCreated;

	return v_ActionButtons;
}


