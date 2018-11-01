/*! \file Map.h
*
* The function of this class will be to control the game's map and all of the 
* functionality required by this class. 
*
*/

#pragma once

#include "defs.h"

#include "GameObject.h"

#include "Grid.h"

class Map : public GameObject
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

	Grid m_clGrid;

	unsigned int m_iCurrentLayer = 0; 

	// Member Functions 

public: 

	//--------------------------------------------------------
	/*! \fn SetupGameMap : This will create the rectangle shape for the main map object. 
	*Param One : Vector2f - This will hold two floats for the width and height of the map. 
	*Param Two : Vector2f - This will hold two floats for the maps X and Y coordinates. 
	*/
	void m_SetUpGameMap(sf::Vector2f dimentions, sf::Vector2f position); 

	//--------------------------------------------------------
	/*! \fn CreateGrid : This will facilitate the formation of all of the cells into a grid object. 
	*
	*/
	void m_CreateGrid(); 

	void m_CreateLakeForMap(); 

	//--------------------------------------------------------
	/*! \fn DrawGameObject : This will be used to draw all of the items required for the map. 
	*Param One : RenderWindow : This is the current game window the objects should be drawn onto. 
	*/
	void m_DrawGameObject(sf::RenderWindow & window) override; 

	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	//--------------------------------------------------------
	/*! \fn SetObjectPos : This will allow for the map object to be moved within the game world. 
	*Param One : Float - The X coordinate for the map object.
	*Param Two : Float - The Y coordinate for the map object.
	*/
	void m_SetObjectPos(float x, float y) override; 



	void m_CheckForLayerChange(int &inputValue); 

	void m_IncreaseLayer();

	void m_DescreaseLayer(); 
};