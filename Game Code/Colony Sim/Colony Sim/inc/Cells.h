/*! \file Cells.h
*
* This will class will hold the information for a single cell within the game. 
* A group of cells will form a either a row or a column.
*
*/

#pragma once

#include "defs.h"

#include "GameObject.h"

enum tileSet
{
	_DIRT = 0x2000,
	_WATER = 0x3000,
	_ROCK = 0x4000
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
	/*! \fn Constructor
	*
	*/
	~Cells();

private:

	// Data Members 

	sf::RectangleShape m_CellBody; 

	int m_iCellId; 

	tileSet m_CurrentTile; 

	std::vector<Cells*> m_Neighbours; 

public:

	// Member Functions

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	void m_CreateCellBody(sf::Vector2f dimentions, sf::Vector2f possition); 

	void m_CreateCellBody(sf::Vector2f dimentions, sf::Vector2f possition, int r, int g, int b);

	void m_AssignTile(unsigned int whichTile); 

	void m_AssignTexture(); 

	void m_AssignNeighbour(Cells &neighbour); 

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	void m_AssignCellId(int id); 

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	int m_GetCellId(); 

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	void m_DrawGameObject(sf::RenderWindow & window) override; 

	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight) override; 

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	void m_SetObjectPos(float x, float y) override; 

	std::vector<Cells*> & m_GetNeighbours(); 

};