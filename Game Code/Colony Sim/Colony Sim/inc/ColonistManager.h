#pragma once

#include "defs.h"

#include "Colonist.h"
#include "Grid.h"

class ColonistManager
{

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	ColonistManager();

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~ColonistManager();

	// Data Members 

private:

	std::vector<Colonist> m_clColonists; 

	// Member Functions 

public:

	void m_AddColonist(int numberOfColonists, sf::Vector2f dimentions, Grid &currentGrid, int startingLayer);

	void m_Update(Grid &CurrentGrid);

	void m_Pathfinding(Grid &CurrentGrid);

	void m_Render(sf::RenderWindow & window);

	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight); 

	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, unsigned int currentLayer);
};