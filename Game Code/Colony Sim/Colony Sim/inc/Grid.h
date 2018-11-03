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

	std::vector<std::vector<std::vector<Cells>>> m_GridMulti; 

public:

	// Member Functions 

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	void m_CreateGrid(unsigned int rows, unsigned int columns, unsigned int layers, sf::RectangleShape gridLocation);

	void m_AssignNeighbours(); 

	void m_CreateLake(int cellX, int cellY, int layer, int numberOfIterations);

	void m_CreateRiver(int startCellX, int startCellY, int endCellX, int endCellY, int layer); 

	void m_AssignTextures(); 

	Cells * m_GetCell(int layer, int x, int y); 

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	void m_DrawGrid(sf::RenderWindow & window, unsigned int layer); 

	void m_CheckItemsForRender(sf::Vector2f topLeft, sf::Vector2f bottomRight, unsigned int layer);

	unsigned int m_GetNumberOfLayers(); 

	unsigned int m_GetNumberOfRows();

	unsigned int m_GetNumberOfColumns(); 

};

