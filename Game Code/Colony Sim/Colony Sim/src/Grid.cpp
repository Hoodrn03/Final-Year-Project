#include "../inc/Grid.h"

Grid::Grid()
{
}

Grid::~Grid()
{
}

void Grid::m_CreateGrid(unsigned int rows, unsigned int columns, unsigned int layers, sf::RectangleShape gridLocation)
{
	// Initalize the height and width values for the cells. 
	float l_fCellWidth = gridLocation.getGlobalBounds().width / rows;
	float l_fCellHeight = gridLocation.getGlobalBounds().height / columns;

	sf::Color l_CellColour = sf::Color(66, 244, 244, 200); 

	// Create a variable which will be used to give the cells a unique identifier. 
	int l_iCurrentId = 0;

	for (unsigned int i = 0; i < layers; i++)
	{
		// Calculate the starting position for the first cell. 
		sf::Vector2f l_CurrentCellPos = sf::Vector2f(gridLocation.getPosition());

		std::vector<std::vector<Cells>> l_Grid;

		std::cout << "Current Layer : " << i << std::endl;

		for (unsigned int j = 0; j < rows; j++)
		{
			// Create a stand-in vector to create the rows for the grid. 
			std::vector<Cells> l_CurrentRow;

			std::cout << "Current Row : " << j << std::endl;

			for (unsigned int k = 0; k < columns; k++)
			{
				// Create a temporary cell for assignement of values. 
				Cells l_CurrentCell;

				std::cout << "Current Column : " << k << std::endl;

				l_CurrentCell.m_CreateCellBody(sf::Vector2f(l_fCellWidth, l_fCellHeight), l_CurrentCellPos, (int)l_CellColour.r, (int)l_CellColour.g, (int)l_CellColour.b);

				l_CurrentCell.m_AssignCellId(l_iCurrentId);

				l_iCurrentId++;

				// Move down on the grid for the next cell.
				l_CurrentCellPos += sf::Vector2f(0, l_fCellHeight);

				// Add the current cell into a vectpr of cells forming a row. 
				l_CurrentRow.push_back(l_CurrentCell);
			}

			// Add the row into the grid, multiple rows will form a grid .
			l_Grid.push_back(l_CurrentRow);

			// Move right along the grid. 
			l_CurrentCellPos += sf::Vector2f(l_fCellWidth, 0);

			// Return the y value to be the top of the grid. 
			l_CurrentCellPos.y = gridLocation.getPosition().y;
		}

		m_GridMulti.push_back(l_Grid); 

		l_CellColour.b -= 50; 

	}
}

void Grid::m_DrawGrid(sf::RenderWindow & window, unsigned int layer)
{
	if (m_GridMulti.size() > layer)
	{
		for (unsigned int i = 0; i < m_GridMulti[layer].size(); i++)
		{
			for (unsigned int j = 0; j < m_GridMulti[layer][i].size(); j++)
			{
				m_GridMulti[layer][i][j].m_DrawGameObject(window);
			}
		}
	}
}

void Grid::m_CheckItemsForRender(sf::Vector2f topLeft, sf::Vector2f bottomRight, unsigned int layer)
{
	if (m_GridMulti.size() > 0)
	{
		for (unsigned int i = 0; i < m_GridMulti[layer].size(); i++)
		{
			for (unsigned int j = 0; j < m_GridMulti[layer][i].size(); j++)
			{
				m_GridMulti[layer][i][j].m_DrawFilter(topLeft, bottomRight);
			}
		}
	}
}

unsigned int Grid::m_GetNumberOfLayers()
{
	return m_GridMulti.size();
}
