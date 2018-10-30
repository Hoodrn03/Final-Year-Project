/*! \file GameMap.cpp
*
* This will hold all of the definitions for the class GameMap.
*
*/

#include "../inc/GameMap.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
Map::Map()
{
}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
Map::~Map()
{
}

//--------------------------------------------------------
/*! \fn SetupGameMap : This will create the rectangle shape for the main map object.
*Param One : Vector2f - This will hold two floats for the width and height of the map.
*Param Two : Vector2f - This will hold two floats for the maps X and Y coordinates.
*/
void Map::m_SetUpGameMap(sf::Vector2f dimentions, sf::Vector2f position)
{
	m_MapObject.setSize(dimentions); 

	m_SetObjectPos(position.x, position.y); 

	m_MapObject.setFillColor(sf::Color::Green); 

	m_CreateGrid(); 

}

//--------------------------------------------------------
/*! \fn CreateGrid : This will facilitate the formation of all of the cells into a grid object.
*
*/
void Map::m_CreateGrid()
{
	m_clGrid.m_CreateGrid(5, 5, 5, m_MapObject);
}

//--------------------------------------------------------
/*! \fn DrawGameObject : This will be used to draw all of the items required for the map.
*Param One : RenderWindow : This is the current game window the objects should be drawn onto.
*/
void Map::m_DrawGameObject(sf::RenderWindow & window)
{
	window.draw(m_MapObject); 

	m_clGrid.m_DrawGrid(window, m_iCurrentLayer); 
}

void Map::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
	m_clGrid.m_CheckItemsForRender(topLeft + sf::Vector2f(-100, -100), bottomRight + sf::Vector2f(100, 100), m_iCurrentLayer);
}

//--------------------------------------------------------
/*! \fn SetObjectPos : This will allow for the map object to be moved within the game world.
*Param One : Float - The X coordinate for the map object.
*Param Two : Float - The Y coordinate for the map object.
*/
void Map::m_SetObjectPos(float x, float y)
{
	m_GameObjectPos = sf::Vector2f(x, y); 

	m_MapObject.setPosition(m_GameObjectPos);
}

void Map::m_CheckForLayerChange(int &inputValue)
{
	switch (inputValue)
	{
	case 1: 
		m_IncreaseLayer(); 
		break;

	case 2: 
		m_DescreaseLayer();
		break;

	default:
		break;
	}

	// Prevent multiple triggers. 
	inputValue = 0;
}

void Map::m_IncreaseLayer()
{
	if (m_iCurrentLayer < (m_clGrid.m_GetNumberOfLayers() - 1))
	{
		m_iCurrentLayer++;

		std::cout << m_iCurrentLayer << std::endl;
	}
}

void Map::m_DescreaseLayer()
{
	if (m_iCurrentLayer > 0)
	{
		m_iCurrentLayer--; 

		std::cout << m_iCurrentLayer << std::endl;
	}
}
