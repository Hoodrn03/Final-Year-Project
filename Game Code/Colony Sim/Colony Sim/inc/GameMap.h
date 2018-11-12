/*! \file Map.h
*
* The function of this class will be to control the game's map and all of the 
* functionality required by this class. 
*
*/

#pragma once

#include "defs.h"

// Components 
#include "GameObject.h"
#include "RandGen.h"

// Associates 
#include "Grid.h"
#include "Pathfinding.h"

/*! \class Will be used to hold the game's map, it will use a grid to place tiles on the map. */
class Map : public GameObject, public RandGen
{
public: 
	
	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Map(); 

public: 

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~Map(); 

	// Data Members 

private: 

	/*! \var This will be used to house the main map object, this will have the grid created overtop of it. */
	sf::RectangleShape m_MapObject; 

	/*! \var This class will hold the grid which will be used for the map. */
	Grid m_clGrid;

	/*! \var The current layer on the map, will be used for drawing a single layer. */
	unsigned int m_iCurrentLayer = 2; 

	/*! \var The ground level for the map, make sure to not use a number higher than the size of the grid.*/
	unsigned int m_iGroundLayer = 2; 

	// Member Functions 

public: 

	//--------------------------------------------------------
	/*! \fn SetupGameMap : This will create the rectangle shape for the main map object. 
	*Param One : Vector2f - This will hold two floats for the width and height of the map. 
	*Param Two : Vector2f - This will hold two floats for the maps X and Y coordinates. 
	*/
	void m_SetUpGameMap(sf::Vector2f dimentions, sf::Vector2f position); 

	//--------------------------------------------------------
	/*! \fn Update : This will be used to update the map every frame.
	*
	*/
	void m_Update(); 

	//--------------------------------------------------------
	/*! \fn CreateGrid : This will facilitate the formation of all of the cells into a grid object. 
	*
	*/
	void m_CreateGrid(); 

	//--------------------------------------------------------
	/*! \fn Generate Map : This will be used upon game startup to generate a random map for the player. 
	*
	*/
	void m_GenerateMap(); 

	//--------------------------------------------------------
	/*! \fn Create Lake for Map : This will initiate the lake generation for the map. 
	*
	*/
	void m_CreateLakeForMap(); 

	//--------------------------------------------------------
	/*! \fn Create River For Map : This will create a river on the game map. 
	*
	*/
	void m_CreateRiverForMap(); 

	//--------------------------------------------------------
	/*! \fn Choose Lake Or River : This will be used to select which water generation method to use for this map. 
	*
	*/
	void m_ChooseLakeOrRiver(int selection);

	//--------------------------------------------------------
	/*! \fn DrawGameObject : This will be used to draw all of the items required for the map. 
	*Param One : RenderWindow : This is the current game window the objects should be drawn onto. 
	*/
	void m_DrawGameObject(sf::RenderWindow & window) override; 

	//--------------------------------------------------------
	/*! \fn Draw Filter : This will be used to limit what is drawn on the screen.
	*Param One : Vector2f : The topleft of the game view. 
	*Param Two : Vector2f : The bottomRight of the game view. 
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	//--------------------------------------------------------
	/*! \fn SetObjectPos : This will allow for the map object to be moved within the game world. 
	*Param One : Float - The X coordinate for the map object.
	*Param Two : Float - The Y coordinate for the map object.
	*/
	void m_SetObjectPos(float x, float y) override; 

	//--------------------------------------------------------
	/*! \fn Check for layer change : This will check if the map's layer should be changed. 
	*Param One : int - The key which was pressed to change the layer. 
	*/
	void m_CheckForLayerChange(int &inputValue); 

	//--------------------------------------------------------
	/*! \fn Increase Layer : Move up one layer on the map. 
	*
	*/
	void m_IncreaseLayer();

	//--------------------------------------------------------
	/*! \fn Decrease Layer : Move down one layer on the map. 
	*
	*/
	void m_DescreaseLayer(); 
};