/*! \file Cells.h
*
* This will class will hold the information for a single cell within the game. 
* A group of cells will form a either a row or a column.
*
*/

#pragma once

#include "defs.h"

#include "GameObject.h"

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

public:

	// Member Functions

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	void m_CreateCellBody(sf::Vector2f dimentions, sf::Vector2f possition); 

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

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	void m_SetObjectPos(float x, float y) override; 

};