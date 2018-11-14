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

	m_GenerateMap();
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

	m_iGroundLayer = m_clGrid.m_GetNumberOfLayers() / 2;

	m_iCurrentLayer = m_iGroundLayer;
}

//--------------------------------------------------------
/*! \fn Generate Map : This will be used upon game startup to generate a random map for the player.
*
*/
void Map::m_GenerateMap()
{
	m_MapObject.setFillColor(sf::Color(0, 191, 255, 255));

	m_CreateGrid();

	// Generate Ground Level.

	if (m_GenerateInt(0, 100) <= 50)
	{
		m_CreateLakeForMap();
	}
	else
	{
		m_CreateRiverForMap();
	}

	m_clGrid.m_CreateRock(m_iGroundLayer);

	m_clGrid.m_CreateDirt(m_iGroundLayer);

	// Generate Underground levels. 

	// The minimum (0) potential layers in the grid to one bellow the ground layer. 
	m_clGrid.m_CreateUndergroundWater(0, m_iGroundLayer - 1);

	m_clGrid.m_CreateUndergroundRock(0, m_iGroundLayer - 1);

	m_clGrid.m_CreateUndergroundDirt(0, m_iGroundLayer - 1);

	// Create Above Ground Levels. 

	// Each layer above the ground and -1 from the total number of layers in the grid (This prevents accessing unexsisting elements). 
	m_clGrid.m_CreateUpperRock(m_iGroundLayer + 1, m_clGrid.m_GetNumberOfLayers() - 1);

	m_clGrid.m_CreateSky(m_iGroundLayer + 1, m_clGrid.m_GetNumberOfLayers() - 1);

	m_clGrid.m_AssignTextures();
}

//--------------------------------------------------------
/*! \fn Create Lake for Map : This will initiate the lake generation for the map.
*
*/
void Map::m_CreateLakeForMap()
{
	/*! \var This will be used to determine the size of the generated lake, this allows for a varied lake for each map. */
	int l_iNumberOfIterations = m_GenerateInt(3, 7);

	m_clGrid.m_CreateLake(m_GenerateInt(0, m_clGrid.m_GetNumberOfRows()), m_GenerateInt(0, m_clGrid.m_GetNumberOfColumns()), m_iGroundLayer, l_iNumberOfIterations);
}

//--------------------------------------------------------
/*! \fn Create River For Map : This will create a river on the game map.
*
*/
void Map::m_CreateRiverForMap()
{

	/*! \var This vector will contain the (x, y) for the start cell on th grid. */
	sf::Vector2i l_StartCell;

	/*! \var This vector will contain the (x, y) for the end cell on th grid. */
	sf::Vector2i l_EndCell;

	// This will select one of the edges for the river to start. 
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

	// This will select one of the edges for the river to end. 
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

	// This will initalize the A* algorithm 
	Pathfinding l_clPathfinding;

	l_clPathfinding.m_InitAlgorithm(m_clGrid.m_GetCell(0, l_StartCell.x, l_StartCell.y), m_clGrid.m_GetCell(0, l_EndCell.x, l_EndCell.y));

	do
	{
		// This will loop continuously until the a path from the start cell to the end cell is found; 
		// using A* it should be pretty quick.
		l_clPathfinding.m_RunAStarAlgorithm();

	} while (!l_clPathfinding.m_CheckForCompletion());

	// This will then use the list of cells to create a river. 
	m_clGrid.m_CreateRiver(l_clPathfinding.m_GetCurrentPath(), m_GenerateInt(2, 5), m_iGroundLayer);
}

int Map::m_GetGroundLevel()
{
	return m_iGroundLayer;
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
	}
}

Grid & Map::m_GetGrid()
{
	return m_clGrid; 
}
