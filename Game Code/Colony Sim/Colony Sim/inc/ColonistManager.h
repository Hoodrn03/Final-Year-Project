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
	std::vector<Colonist> v_clColonists;

public:

	/*! \var This will allow for the game to check if one or more colonist is selected. */
	bool m_bColonistSelected = false;

	/*! \var This will be used to check if the buttons have been created.  */
	bool m_bButtonsCreated = false;

	/*! \var This will check if the buttons have been removed. */
	bool m_bButtonsRemoved = false; 

	/*! \var This is a list of buttons to be used by the user interface. */
	std::vector<tgui::Button::Ptr> v_ListOfButtons;

	// Member Functions 

public:

	//--------------------------------------------------------\\
	//						Setup 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Add Colonist : This will be used to add a new colonist into the vector. 
	*Param One : int - This will be the total number of colonists which should be added to the game. 
	*Param Two : Vector2f - The dimentions for the colonists (height and width). 
	*Param Three : Grid - The grid which is overlayed onto the current game map. 
	*Param Four : int - The layer which the colonists should be spawend onto. 
	*/
	void m_AddColonist(int numberOfColonists, sf::Vector2f dimentions, Grid &currentGrid, int startingLayer);

	//--------------------------------------------------------\\
	//						Update 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Update : This will update the logic for all of the colonists. 
	*Param One : Grid - the current grid which is overlayed onto the game map. 
	*/
	void m_Update(Grid &CurrentGrid);

	//--------------------------------------------------------\\
	//						Pathfinding
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Pathfinding : This will be used to manage the colonist's current path. 
	*Param One : Grid - the current grid which is overlayed onto the game map. 
	*/
	void m_Pathfinding(Grid &CurrentGrid);

	//--------------------------------------------------------\\
	//						Rendering
	//--------------------------------------------------------\\

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

	//--------------------------------------------------------\\
	//						Seletion
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Select Colonist : This will be used to select colonists. 
	*Param One : Vector2f - The top left for the mouse's selection box. 
	*Param Two : Vector2f - The bottom right for the mouse's selection box. 
	*Param Three : Bool - The value for if the mouse button is down. 
	*/
	void m_SelectColonist(sf::Vector2f topLeft, sf::Vector2f bottomRight, bool mouseDown); 

	//--------------------------------------------------------
	/*! \fn Check For Selected : Used to check for the selected colonists. 
	*
	*/
	void m_CheckForSelected(); 

	//--------------------------------------------------------\\
	//						Job System
	//--------------------------------------------------------\\


	//--------------------------------------------------------\\
	//						Buttons 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Create Colonist Action Buttons : Used to create the buttons which will be used for the colonists. 
	*Param One : Font - The font which will be used for the game. 
	*Param Two : RenderWindow - The main window for the game. 
	*/
	void m_CreateColonistActionButtons(sf::Font gameFont, sf::RenderWindow &window);

	//--------------------------------------------------------
	/*! \fn Get Colonist Buttons : This will be used to get the colonist buttons. 
	*
	*/
	std::vector<tgui::Button::Ptr> m_GetColonistButtons(); 
};