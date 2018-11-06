/*! \file Cells.cpp
*
* This will hold all of the definitions for the class Cells.
*
*/

#include "../inc/Cells.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
Cells::Cells()
{
}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
Cells::~Cells()
{
}

//--------------------------------------------------------
/*! \fn Create Cell Body : This will be used to initalize this cell.
*Param One : Vector2f - The height and width of the cell.
*Param Two : Vector2f - The x and y coordinates for the cell.
*/
void Cells::m_CreateCellBody(sf::Vector2f dimentions, sf::Vector2f possition)
{
	m_CellBody.setSize(dimentions); 

	m_SetObjectPos(possition.x, possition.y); 

	m_CellBody.setFillColor(sf::Color::Magenta); 

	m_CellBody.setOutlineColor(sf::Color::Black);

	m_CellBody.setOutlineThickness(m_CellBody.getGlobalBounds().width * 0.1f); 
}

//--------------------------------------------------------
/*! \fn SetGridPos : This will be used to assign a position to the cell.
*Param One : int - The x position on for the cell on the grid.
*Param Two : int - The y position on for the cell on the grid.
*/
void Cells::m_SetGridPos(int x, int y)
{
	m_GridPosition.x = x;
	m_GridPosition.y = y; 
}

//--------------------------------------------------------
/*! \fn GetGridPos : This will return the current position of the cell.
*
*/
gridPos Cells::m_GetGridPos()
{
	return m_GridPosition;
}

//--------------------------------------------------------
/*! \fn Create Cell Body : This will be used to initalize this cell, Overload to set colour.
*Param One : Vector2f - The height and width of the cell.
*Param Two : Vector2f - The x and y coordinates for the cell.
*Param Three : int - Red value.
*Param Four : int - Green value.
*Param FIve : int - Blue value.
*/
void Cells::m_CreateCellBody(sf::Vector2f dimentions, sf::Vector2f possition, int r, int g, int b)
{
	m_CellBody.setSize(dimentions);

	m_SetObjectPos(possition.x, possition.y);

	m_CellBody.setFillColor(sf::Color(r, g, b, 200));

	m_CellBody.setOutlineColor(sf::Color::Black);

	m_CellBody.setOutlineThickness(m_CellBody.getGlobalBounds().width * 0.01f);
}

//--------------------------------------------------------
/*! \fn SetCellColour : This will change the colour of the cell.
*Param One - int : THe amount of red in the cell.
*Param Two - int : THe amount of green in the cell.
*Param Three - int : THe amount of blue in the cell.
*/
void Cells::m_SetCellColour(int r, int g, int b)
{
	m_CellBody.setFillColor(sf::Color(r, g, b, 255)); 
}

//--------------------------------------------------------
/*! \fn Assign Tile : This will be used to set tile value for this cell.
*Param One : unsigned int - 1 Dirt, 2 Water, 3 Rock, else null.
*/
void Cells::m_AssignTile(unsigned int whichTile)
{
	switch (whichTile)
	{
	case 1:
		m_CurrentTile = _DIRT;
		break;

	case 2:
		m_CurrentTile = _WATER;
		break;

	case 3:
		m_CurrentTile = _ROCK;
		break;

	default:

		std::cout << "Invalid Tile Selection" << std::endl;
		
		break;
	}
}

//--------------------------------------------------------
/*! \fn Assign Texture : This will be used to change the colour of the cell equil to its assigned tile.
*
*/
void Cells::m_AssignTexture()
{
	switch (m_CurrentTile)
	{
	case _DIRT:
		m_CellBody.setFillColor(sf::Color::White);
		break;

	case _WATER:
		m_CellBody.setFillColor(sf::Color::Blue);
		break;

	case _ROCK:
		m_CellBody.setFillColor(sf::Color::Red);
		break;

	default:
		m_CellBody.setFillColor(sf::Color::Magenta); 
		break;
	}

}

//--------------------------------------------------------
/*! \fn Assign Neighbour : This will allow for a neighbour to be added to the vector.
*Param One : Cells - A cell next to this one.
*/
void Cells::m_AssignNeighbour(Cells &neighbour)
{
	m_Neighbours.push_back(&neighbour); 
}

//--------------------------------------------------------
/*! \fn Assign Cell Id : Add a unique identifier to this cell.
*Param One : int : a number identifier for this cell.
*/
void Cells::m_AssignCellId(int id)
{
	m_iCellId = id; 
}

//--------------------------------------------------------
/*! \fn Get Cell Id : This will be used to read the cell's id.
*
*/
int Cells::m_GetCellId()
{
	return m_iCellId;
}

//--------------------------------------------------------
/*! \fn Draw Game Object : Used to draw the cell onto the game window.
*Param One : RenderWindow - The game window the object is being drawn onto.
*/
void Cells::m_DrawGameObject(sf::RenderWindow & window)
{
	if (m_DrawItem == _DRAW)
	{
		window.draw(m_CellBody);
	} 
}

//--------------------------------------------------------
/*! \fn Draw Filter : This will be used to check if this cell should be draw.
*Param One : Vector2f - The top left of the view.
*Param Two : Vector2f - The bottom right of the view.
*/
void Cells::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
	if (((m_CellBody.getPosition().x > topLeft.x) && (m_CellBody.getPosition().y > topLeft.y))
		&& ((m_CellBody.getPosition().x < bottomRight.x) && (m_CellBody.getPosition().y < bottomRight.y)))
	{
		m_DrawItem = _DRAW;
	}
	else
	{
		m_DrawItem = _NO_DRAW;
	}
}

//--------------------------------------------------------
/*! \fn Set Object Pos : This will place the cell in the game world.
*Param One : float - x Coordinate.
*Param Two : float - y Coordinate.
*/
void Cells::m_SetObjectPos(float x, float y)
{
	m_GameObjectPos = sf::Vector2f(x, y); 

	m_CellBody.setPosition(m_GameObjectPos); 
}

//--------------------------------------------------------
/*! \fn Get Neighbours : This will be used to get access to the list of neighbours.
*
*/
std::vector<Cells*>& Cells::m_GetNeighbours()
{
	return m_Neighbours;
}
