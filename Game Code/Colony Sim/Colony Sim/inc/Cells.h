/*! \file Cells.h
*
* This will class will hold the information for a single cell within the game. 
* A group of cells will form a either a row or a column.
*
*/

#pragma once

#include "defs.h"

#include "GameObject.h"

/*! \enum This will be used to set the cells tile */
enum tileSet
{
	_DIRT = 0x2000, /*!< This will make the tile Dirt. */
	_WATER = 0x3000, /*!< This will make the tile Water. */
	_ROCK = 0x4000 /*!< This will make the tile Rock. */
};

enum huristicCost
{
	_DIAGONAL = 14,
	_ACROSS = 10
};

struct gridPos
{
	float x, y; 
};

class Cells : public GameObject
{

public: 
	
	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Cells(); 

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor 
	*
	*/
	~Cells();

private:

	// Data Members 

	/*! \var This will be used to display the cell on the screen. */
	sf::RectangleShape m_CellBody; 

	/*! \var The cells unique identifier. */
	int m_iCellId; 

	/*! \var Determines which tile the cell will be displayed as. */
	tileSet m_CurrentTile; 

	/*! \var A list of all the cells around this one Max 8, Min 3*/
	std::vector<Cells*> m_Neighbours; 

	gridPos m_GridPosition; 

public:

	/*! \var This will hold a reference to a cell that leads to this one. */
	Cells * m_ParentCell;

	int m_iGScore; 

	int m_iHScore; 

	int m_iFScore; 

public:

	// Member Functions

	//--------------------------------------------------------
	/*! \fn Create Cell Body : This will be used to initalize this cell. 
	*Param One : Vector2f - The height and width of the cell. 
	*Param Two : Vector2f - The x and y coordinates for the cell. 
	*/
	void m_CreateCellBody(sf::Vector2f dimentions, sf::Vector2f possition); 

	void m_SetGridPos(int x, int y);

	gridPos m_GetGridPos(); 

	//--------------------------------------------------------
	/*! \fn Create Cell Body : This will be used to initalize this cell, Overload to set colour.
	*Param One : Vector2f - The height and width of the cell.
	*Param Two : Vector2f - The x and y coordinates for the cell.
	*Param Three : int - Red value.
	*Param Four : int - Green value. 
	*Param FIve : int - Blue value. 
	*/
	void m_CreateCellBody(sf::Vector2f dimentions, sf::Vector2f possition, int r, int g, int b);

	void m_SetCellColour(int r, int g, int b); 

	//--------------------------------------------------------
	/*! \fn Assign Tile : This will be used to set tile value for this cell.
	*Param One : unsigned int - 1 Dirt, 2 Water, 3 Rock, else null. 
	*/
	void m_AssignTile(unsigned int whichTile); 

	//--------------------------------------------------------
	/*! \fn Assign Texture : This will be used to change the colour of the cell equil to its assigned tile.  
	*
	*/
	void m_AssignTexture(); 

	//--------------------------------------------------------
	/*! \fn Assign Neighbour : This will allow for a neighbour to be added to the vector. 
	*Param One : Cells - A cell next to this one. 
	*/
	void m_AssignNeighbour(Cells &neighbour); 

	//--------------------------------------------------------
	/*! \fn Assign Cell Id : Add a unique identifier to this cell. 
	*Param One : int : a number identifier for this cell. 
	*/
	void m_AssignCellId(int id); 

	//--------------------------------------------------------
	/*! \fn Get Cell Id : This will be used to read the cell's id. 
	*
	*/
	int m_GetCellId(); 

	//--------------------------------------------------------
	/*! \fn Draw Game Object : Used to draw the cell onto the game window.
	*Param One : RenderWindow - The game window the object is being drawn onto.  
	*/
	void m_DrawGameObject(sf::RenderWindow & window) override; 

	//--------------------------------------------------------
	/*! \fn Draw Filter : This will be used to check if this cell should be draw. 
	*Param One : Vector2f - The top left of the view. 
	*Param Two : Vector2f - The bottom right of the view. 
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight) override; 

	//--------------------------------------------------------
	/*! \fn Set Object Pos : This will place the cell in the game world. 
	*Param One : float - x Coordinate. 
	*Param Two : float - y Coordinate. 
	*/
	void m_SetObjectPos(float x, float y) override; 

	//--------------------------------------------------------
	/*! \fn Get Neighbours : This will be used to get access to the list of neighbours. 
	*
	*/
	std::vector<Cells*> & m_GetNeighbours(); 

};