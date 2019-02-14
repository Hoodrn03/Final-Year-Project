/*! \file This will manage all of ten games ingame resources like wood or stone. */

#pragma once

#include "defs.h"

#include "Grid.h"
#include "WoodResource.h"

/*! \class This will be used to manage all of the games resources. */
class ResourceManagement
{

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	ResourceManagement();

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~ResourceManagement();

	// Data Memebers 

private: 

	/*! \var This will hold all of the growing tree objects in the game. */
	std::vector<WoodResource> v_clTrees;

	/*! \var This will hold the current action the player is performing. */
	currentAction m_CurretAction = _NULL; 

	// Member Functions 

public: 

	//--------------------------------------------------------
	//						Setup 
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn AddTrees : This will be used to add a number of trees into the game.
	*Param One : int - The number of trees to add. 
	*Param Two : float - The maximum radius for the spawned trees.
	*Param Three : int - The layer to spawn the trees. 
	*Param Four : Grid - The grid reference to spawn the trees onto. 
	*/
	void m_AddTrees(int numberOfTrees, float maxRadius, int layer, Grid &grid);

	//--------------------------------------------------------
	//						Rendering
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn DrawTrees : Draws the trees into the game. 
	*Param One : RenderWindow - The main game window. 
	*/
	void m_DrawTrees(sf::RenderWindow &window); 

	//--------------------------------------------------------
	/*! \fn DrawFilter : Used to limit the game objects from being drawn. 
	*Param One : Vector2f - The top left of the game's view. 
	*Param Two : Vector2f - The bottom right of the game's view. 
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	//--------------------------------------------------------
	/*! \fn DrawFilter : Used to limit the game objects from being drawn.
	*Param One : Vector2f - The top left of the game's view.
	*Param Two : Vector2f - The bottom right of the game's view.
	*Param Three : int - The current layer the player is on. 
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, int currentLayer);

	//--------------------------------------------------------
	//						Update 
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn Update : Update the current game resources. 
	*
	*/
	void m_Update(); 

	//--------------------------------------------------------
	//					Removing Resources
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn AssignAction : Used to update the current action the player is performing. 
	*Param One : currentAction - The new action to perform. 
	*/
	void m_AssignAction(currentAction newAction);

	//--------------------------------------------------------
	//					Seleting Resources 
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn SelectResource : Used to select a number of resources within the game world based on position. 
	*Param One : Vector2f - The top left of the selection box drawn by the mouse.
	*Param Two : Vector2f - The bottom right of the selection box drawn by the mouse
	*/
	void m_SelectResources(sf::Vector2f m_TopLeft, sf::Vector2f bottomRight);

	Cells * m_FindClosestTree(sf::Vector2f otherObject); 
};
