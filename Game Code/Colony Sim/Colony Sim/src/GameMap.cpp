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

	if (m_GenerateInt(0, 100) <= 50)
	{
		m_ChooseLakeOrRiver(0);
	}
	else
	{
		m_ChooseLakeOrRiver(1); 
	}

	m_clGrid.m_AssignTextures();

}

//--------------------------------------------------------
/*! \fn Update : This will be used to update the map every frame.
*
*/
void Map::m_Update()
{



}

//--------------------------------------------------------
/*! \fn CreateGrid : This will facilitate the formation of all of the cells into a grid object.
*
*/
void Map::m_CreateGrid()
{
	m_clGrid.m_CreateGrid(50, 50, 5, m_MapObject);
}

//--------------------------------------------------------
/*! \fn Create Lake for Map : This will initiate the lake generation for the map.
*
*/
void Map::m_CreateLakeForMap()
{
	m_clGrid.m_CreateLake(m_GenerateInt(0, m_clGrid.m_GetNumberOfRows()), m_GenerateInt(0, m_clGrid.m_GetNumberOfColumns()), 0, 5);

	std::cout << "Lake Created" << std::endl;
}

//--------------------------------------------------------
/*! \fn Create River For Map : This will create a river on the game map.
*
*/
void Map::m_CreateRiverForMap()
{
	sf::Vector2i l_StartCell;
	sf::Vector2i l_EndCell;

	if (m_GenerateInt(0, 100) <= 50)
	{
		l_StartCell.y = (m_GenerateInt(0, m_clGrid.m_GetNumberOfColumns()));

		l_StartCell.x = 0;

	}
	else
	{
		l_StartCell.y = 0;

		l_StartCell.x = (m_GenerateInt(0, m_clGrid.m_GetNumberOfRows()));

	}


	if (m_GenerateInt(0, 100) <= 50)
	{
		l_EndCell.y = m_clGrid.m_GetNumberOfColumns() - 1;

		l_EndCell.x = (m_GenerateInt(0, m_clGrid.m_GetNumberOfRows()));
	}
	else
	{
		l_EndCell.y = (m_GenerateInt(0, m_clGrid.m_GetNumberOfColumns()));

		l_EndCell.x = m_clGrid.m_GetNumberOfRows() - 1;
	}

	Pathfinding l_clPathfinding; 

	l_clPathfinding.m_InitAlgorithm(m_clGrid.m_GetCell(0, l_StartCell.x, l_StartCell.y), m_clGrid.m_GetCell(0, l_EndCell.x, l_EndCell.y));

	do
	{
		l_clPathfinding.m_RunAStarAlgorithm();

	} while (!l_clPathfinding.m_CheckForCompletion());

	m_clGrid.m_CreateRiver(l_clPathfinding.m_GetCurrentPath(), m_GenerateInt(2, 5), 0);

	std::cout << "River Created" << std::endl;
}

//--------------------------------------------------------
/*! \fn Choose Lake Or River : This will be used to select which water generation method to use for this map.
*
*/
void Map::m_ChooseLakeOrRiver(int selection)
{
	switch (selection)
	{
	case 0: 
		m_CreateLakeForMap();
		break;

	case 1:
		m_CreateRiverForMap(); 
			break;

	default:
		std::cout << "Invalid Selection." << std::endl;
		break;
	}
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

//--------------------------------------------------------
/*! \fn Draw Filter : This will be used to limit what is drawn on the screen.
*Param One : Vector2f : The topleft of the game view.
*Param Two : Vector2f : The bottomRight of the game view.
*/
void Map::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
	m_clGrid.m_CheckItemsForRender(topLeft + sf::Vector2f(-50, -50), bottomRight + sf::Vector2f(50, 50), m_iCurrentLayer);
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

//--------------------------------------------------------
/*! \fn Check for layer change : This will check if the map's layer shoul be changed.
*Param One : int - The key which was pressed to chnge the layer.
*/
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

//--------------------------------------------------------
/*! \fn Check for layer change : This will check if the map's layer shoul be changed.
*Param One : int - The key which was pressed to chnge the layer.
*/
void Map::m_IncreaseLayer()
{
	if (m_iCurrentLayer < (m_clGrid.m_GetNumberOfLayers() - 1))
	{
		m_iCurrentLayer++;

		std::cout << m_iCurrentLayer << std::endl;
	}
}

//--------------------------------------------------------
/*! \fn Decrease Layer : Move down one layer on the map.
*
*/
void Map::m_DescreaseLayer()
{
	if (m_iCurrentLayer > 0)
	{
		m_iCurrentLayer--; 

		std::cout << m_iCurrentLayer << std::endl;
	}
}
