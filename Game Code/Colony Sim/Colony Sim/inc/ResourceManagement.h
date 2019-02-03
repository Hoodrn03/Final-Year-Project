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

	currentAction m_CurretAction = _NULL; 

	// Member Functions 

public: 

	//--------------------------------------------------------
	/*! \fn AddTrees : This will be used to add a number of trees into the game.
	*Param One : int - The number of trees to add. 
	*Param Two : float - The maximum radius for the spawned trees.
	*Param Three : int - The layer to spawn the trees. 
	*Param Four : Grid - The grid reference to spawn the trees onto. 
	*/
	void m_AddTrees(int numberOfTrees, float maxRadius, int layer, Grid &grid);

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
	/*! \fn Update : Update the current game resources. 
	*
	*/
	void m_Update(); 

	void m_CutTreeAction(currentAction newAction); 

	void m_SelectResources(sf::Vector2f m_TopLeft, sf::Vector2f bottomRight);
};
