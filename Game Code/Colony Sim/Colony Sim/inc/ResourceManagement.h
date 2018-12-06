#pragma once

#include "defs.h"

#include "Grid.h"
#include "WoodResource.h"

class ResourceManagement
{

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	ResourceManagement();

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~ResourceManagement();

	// Data Memebers 

private: 

	std::vector<WoodResource> m_Trees; 

	// Member Functions 

public: 

	void m_AddTrees(int numberOfTrees, float maxRadius, int layer, Grid &grid);

	void m_DrawTrees(sf::RenderWindow &window); 

	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, int currentLayer);

	void m_Update(); 

};
