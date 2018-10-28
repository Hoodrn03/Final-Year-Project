#pragma once

#include "defs.h"

#include "Cells.h"

class Grid
{

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Grid();

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	~Grid();

private:

	// Data Members 

	std::vector<std::vector<Cells>> m_Grid; 

public:

	// Member Functions 

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	void m_CreateGrid(unsigned int rows, unsigned int columns, sf::RectangleShape gridLocation);

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	void m_DrawGrid(sf::RenderWindow & window); 


};

