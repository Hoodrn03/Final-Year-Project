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
/*! \fn Create Cell Body : This will be used to initalize This cell.
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

	m_SetCellCentre();
}

//--------------------------------------------------------
/*! \fn Create Cell Body (Overload) : This will be used to initalize This cell.
*Param One : Vector2f - The height and width of the cell.
*Param Two : Vector2f - The x and y coordinates for the cell.
*Param Three : int - Red value.
*Param Four : int - Green value.
*Param Five : int - Blue value.
*/
void Cells::m_CreateCellBody(sf::Vector2f dimentions, sf::Vector2f possition, int r, int g, int b)
{
	m_CellBody.setSize(dimentions);

	m_SetObjectPos(possition.x, possition.y);

	m_CellBody.setFillColor(sf::Color(r, g, b, 200));

	m_CellBody.setOutlineColor(sf::Color::Black);

	m_CellBody.setOutlineThickness(m_CellBody.getGlobalBounds().width * 0.01f);

	m_SetCellCentre();
}

//--------------------------------------------------------
/*! \fn Check Cell Bounds : This will be used to check if a point is inside This cell.
*Param One : float - The x coordine of the point.
*Param Two : float - The y coordine of the point.
*/
bool Cells::m_CheckCellBounds(float x, float y)
{
	if ((x >= m_GetObjectPos().x && y >= m_GetObjectPos().y) &&
		(x <= m_GetObjectPos().x + m_CellBody.getGlobalBounds().width && y <= m_GetObjectPos().y + m_CellBody.getGlobalBounds().height))
	{
		return true; 
	}

	return false;
}

//--------------------------------------------------------
/*! \fn SetGridPos : This will be used to assign a position to the cell.
*Param One : int - The x position on for the cell on the grid.
*Param Two : int - The y position on for the cell on the grid.
*/
void Cells::m_SetGridPos(int x, int y)
{
	m_GridPosition.x = (float)x;
	m_GridPosition.y = (float)y; 
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
/*! \fn SetLayer : This will allow for the layer of the cell to be set.
*
*/
void Cells::m_SetLayer(int layer)
{
	m_Layer = layer; 
}

//--------------------------------------------------------
/*! \fn Get Layer : Will return the value for the layer the cell is currently on.
*
*/
int Cells::m_GetLayer()
{
	return m_Layer;
}

//--------------------------------------------------------
/*! \fn Set Cell Centre : This will be used to update the current cell centre, using its position and dimentions.
*
*/
void Cells::m_SetCellCentre()
{
	m_CellCentre.x = m_GameObjectPos.x + (m_CellBody.getGlobalBounds().width * 0.5f);
	m_CellCentre.y = m_GameObjectPos.y + (m_CellBody.getGlobalBounds().height * 0.5f);
}

//--------------------------------------------------------
/*! \fn Get Cell Centre : This will return the cells centre point in world space.
*
*/
sf::Vector2f Cells::m_GetCellCentre()
{
	return m_CellCentre;
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
/*! \fn Assign Tile : This will be used to set tile value for This cell.
*Param One : unsigned int - 1 Dirt, 2 Water, 3 Rock, else null.
*/
void Cells::m_AssignTile(tileSet whichTile)
{
	m_CurrentTile = whichTile;
}

//--------------------------------------------------------
/*! \fn Assign Texture : This will be used to change the colour of the cell equil to its assigned tile.
*
*/
void Cells::m_AssignColours()
{
	switch (m_CurrentTile)
	{
	case _DIRT:
		m_CellBody.setFillColor(m_DirtColour);
		break;

	case _WATER:
		m_CellBody.setFillColor(m_WaterColour);
		break;

	case _ROCK:
		m_CellBody.setFillColor(m_RockColour);
		break;

	case _SKY:
		m_CellBody.setFillColor(m_SkyColour);
		break;

	default:
		m_CellBody.setFillColor(sf::Color::Magenta); 
		break;
	}

}

//--------------------------------------------------------
/*! \fn Assign Neighbour : This will allow for a neighbour to be added to the vector.
*Param One : Cells - A cell next to This one.
*/
void Cells::m_AssignNeighbour(Cells &neighbour)
{
	m_Neighbours.push_back(&neighbour); 
}

//--------------------------------------------------------
/*! \fn Assign Cell Id : Add a unique identifier to This cell.
*Param One : int : a number identifier for This cell.
*/
void Cells::m_AssignCellId(int id)
{
	m_iCellId = id; 
}

//--------------------------------------------------------
/*! \fn Update : This will be used to update the game logic for This object.
*
*/
void Cells::m_Update()
{
}

//--------------------------------------------------------
/*! \fn Get Cell Id : This will be used to read the cell's id.
*
*/
int Cells::m_GetCellId()
{
	if (this == nullptr)
	{
		return -1; 
	}
	else
	{
		return m_iCellId;
	}
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
/*! \fn Draw Filter : This will be used to check if This cell should be draw.
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

//--------------------------------------------------------
/*! \fn Get Tile : This will be used to check the current tile value for the cell.
*
*/
tileSet Cells::m_GetTile()
{
	return m_CurrentTile;
}

//--------------------------------------------------------
/*! \fn Get Cell Width : This will return the current width for the cell.
*
*/
float Cells::m_GetCellWidth()
{
	return m_CellBody.getGlobalBounds().width;
}

//--------------------------------------------------------
/*! \fn Get Cell Height : This will return the current height for the cell.
*
*/
float Cells::m_GetCellHeight()
{
	return m_CellBody.getGlobalBounds().height;
}
