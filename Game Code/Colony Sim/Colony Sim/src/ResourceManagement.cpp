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

		l_TempTree.m_CreateTree(maxRadius, grid.m_GetRandomDirtCell(layer)->m_GetCellCentre(), layer); 

		v_clTrees.push_back(l_TempTree);
	}

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

void ResourceManagement::m_CutTreeAction(currentAction newAction)
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


