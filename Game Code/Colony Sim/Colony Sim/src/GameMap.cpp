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
	m_clGrid.m_CreateGrid(25, 25, m_MapObject); 
}

//--------------------------------------------------------
/*! \fn DrawGameObject : This will be used to draw all of the items required for the map.
*Param One : RenderWindow : This is the current game window the objects should be drawn onto.
*/
void Map::m_DrawGameObject(sf::RenderWindow & window)
{
	window.draw(m_MapObject); 

	m_clGrid.m_DrawGrid(window); 
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
