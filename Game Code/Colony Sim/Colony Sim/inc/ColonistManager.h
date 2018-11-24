/*! \file ColonistManager.h
*
* This will be used to manage and maintain a list of all of the colonists, it's main functionality will be to 
* condense the total calls for multiple colonists to a single function. This class will also make it easy to add 
* or remove one or more colonists at a single time. 
*
*/

#pragma once

#include "defs.h"

#include "Colonist.h"
#include "Grid.h"

/*! \class This class will hold a vector of colonists and manage all of their functions at once. */
class ColonistManager
{

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	ColonistManager();

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~ColonistManager();

	// Data Members 

private:

	/*! \var This will hold all of the colonists currently in the game. */
	std::vector<Colonist> m_clColonists; 

	// Member Functions 

public:

	//--------------------------------------------------------
	/*! \fn Add Colonist : This will be used to add a new colonist into the vector. 
	*Param One : int - This will be the total number of colonists which should be added to the game. 
	*Param Two : Vector2f - The dimentions for the colonists (height and width). 
	*Param Three : Grid - The grid which is overlayed onto the current game map. 
	*Param Four : int - The layer which the colonists should be spawend onto. 
	*/
	void m_AddColonist(int numberOfColonists, sf::Vector2f dimentions, Grid &currentGrid, int startingLayer);

	//--------------------------------------------------------
	/*! \fn Update : This will update the logic for all of the colonists. 
	*Param One : Grid - the current grid which is overlayed onto the game map. 
	*/
	void m_Update(Grid &CurrentGrid);

	//--------------------------------------------------------
	/*! \fn Pathfinding : This will be used to manage the colonist's current path. 
	*Param One : Grid - the current grid which is overlayed onto the game map. 
	*/
	void m_Pathfinding(Grid &CurrentGrid);

	//--------------------------------------------------------
	/*! \fn Render : This will draw all of the colonists onto the game window. 
	*Param One : RenderWindow : The current game window. 
	*/
	void m_Render(sf::RenderWindow & window);

	//--------------------------------------------------------
	/*! \fn Draw Filter : This will be used to limit if the colonists are drawn or not. 
	*Param One : Vector2f - The top left of the game view.
	*Param Two : Vector2f - The bottom right of the game view.
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight); 

	//--------------------------------------------------------
	/*! \fn Draw Filter (Overload) : This will be used to limit if the colonists are drawn or not.
	*Param One : Vector2f - The top left of the game view.
	*Param Two : Vector2f - The bottom right of the game view.
	*Param Three : unsinged int : The current layer the window is displaying. 
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, unsigned int currentLayer);
};