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

	// Create a variable which will be used to give the cells a unique identifier. 
	int l_iCurrentId = 0;

	for (unsigned int i = 0; i < layers; i++)
	{
		// Calculate the starting position for the first cell. 
		sf::Vector2f l_CurrentCellPos = sf::Vector2f(gridLocation.getPosition());

		std::vector<std::vector<Cells>> l_Grid;

		// std::cout << "Current Layer : " << i << std::endl;

		for (unsigned int j = 0; j < rows; j++)
		{
			// Create a stand-in vector to create the rows for the grid. 
			std::vector<Cells> l_CurrentRow;

			// std::cout << "Current Row : " << j << std::endl;

			for (unsigned int k = 0; k < columns; k++)
			{
				// Create a temporary cell for assignement of values. 
				Cells l_CurrentCell;

				// std::cout << "Current Column : " << k << std::endl;

				l_CurrentCell.m_CreateCellBody(sf::Vector2f(l_fCellWidth, l_fCellHeight), l_CurrentCellPos);

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
	}

	m_AssignNeighbours(); 

}

void Grid::m_AssignNeighbours()
{
	if (m_GridMulti.size() > 0)
	{
		for (int i = 0; i < (int)m_GridMulti.size(); i++)
		{
			for (int j = 0; j < (int)m_GridMulti[i].size(); j++)
			{
				for (int k = 0; k < (int)m_GridMulti[i][j].size(); k++)
				{

					if (j - 1 >= 0)
					{
						// West Cell

						m_GridMulti[i][j][k].m_AssignNeighbour(m_GridMulti[i][j - 1][k]); 
					}

					if (k - 1 >= 0)
					{
						// North Cell

						m_GridMulti[i][j][k].m_AssignNeighbour(m_GridMulti[i][j][k - 1]);
					}

					if (j + 1 < (int)m_GridMulti[i].size())
					{
						// East Cell

						m_GridMulti[i][j][k].m_AssignNeighbour(m_GridMulti[i][j + 1][k]);
					}

					if (k + 1 < (int)m_GridMulti[i][j].size())
					{
						// South Cell

						m_GridMulti[i][j][k].m_AssignNeighbour(m_GridMulti[i][j][k + 1]);
					}

					if (k - 1 >= 0 && j - 1 >= 0)
					{
						// North West Cell

						m_GridMulti[i][j][k].m_AssignNeighbour(m_GridMulti[i][j - 1][k - 1]);
					}

					if (k - 1 >= 0 && j + 1 < (int)m_GridMulti[i].size())
					{
						// North East Cell

						m_GridMulti[i][j][k].m_AssignNeighbour(m_GridMulti[i][j + 1][k - 1]);
					}

					if (k + 1 < (int)m_GridMulti[i][j].size() && j - 1 >= 0)
					{
						// South West Cell

						m_GridMulti[i][j][k].m_AssignNeighbour(m_GridMulti[i][j - 1][k + 1]);
					}

					if (k + 1 < (int)m_GridMulti[i][j].size() && j + 1 < (int)m_GridMulti[i].size())
					{
						// South East Cell

						m_GridMulti[i][j][k].m_AssignNeighbour(m_GridMulti[i][j + 1][k + 1]);
					}

				}
			}
		}
	}
}

void Grid::m_CreateLake(int cellX, int cellY, int layer)
{
	// Local Variables. 

	int l_iTilePlacement = 10;

	int l_iNumberOfIterations = 5;

	int l_iChanceDegridation = 15; 

	int l_iTotalChance = l_iNumberOfIterations * l_iChanceDegridation; 

	std::vector<Cells*> l_WaterTiles;

	std::vector<Cells*> l_CellsToAdd;

	// Set Start of lake. 

	m_GridMulti[layer][cellX][cellY].m_AssignTile(2); 

	l_CellsToAdd.push_back(&m_GridMulti[layer][cellX][cellY]); 
 
	// Begin Lake Generation. 

	for (int i = 0; i < l_iNumberOfIterations; i++)
	{
		for (int j = 0; j < l_CellsToAdd.size(); j++)
		{
			// Loop throgh the neighbours of cells to add and add them into the water tiles. 

			for (int k = 0; k < l_CellsToAdd[j]->m_GetNeighbours().size(); k++)
			{
				// If the neighbour is already inside the water tiles, don't add multiple copies of them

				if (std::find(l_WaterTiles.begin(), l_WaterTiles.end(), l_CellsToAdd[j]->m_GetNeighbours()[k]) != l_WaterTiles.end())
				{
					
				}
				else
				{
					l_WaterTiles.push_back(l_CellsToAdd[j]->m_GetNeighbours()[k]);
				}
			}
		}

		// Clear cells to add to prevent multiple copies being added. 

		l_CellsToAdd.clear(); 

		for (int j = 0; j < l_WaterTiles.size(); j++)
		{
			int l_iRandom;

			// Generate a Random Number. 

			l_iRandom = rand() % l_iTilePlacement + 1;

			// std::cout << "Current Chance : " << l_iRandom << std::endl;


			// The chance for a water tile to be placed will be a third of the total chance. 
			// The first couple will be guarenteed to be a water tile, but the chance of them 
			// being placed will be lowered with each iteration. 
			if (l_iRandom <= l_iTotalChance / 3)
			{
				l_WaterTiles[j]->m_AssignTile(2);
			}

			for (int k = 0; k < l_WaterTiles[j]->m_GetNeighbours().size(); k++)
			{
				// Loop through the water tiles and add the neighbours of the current water tiles into the cells to add.
				// This will allow for more tiles to become water. 

				l_CellsToAdd.push_back(l_WaterTiles[j]->m_GetNeighbours()[k]); 
			}
		}

		// Add to the current tile placement value lowering the chance for a tile to be placed as water. 

		l_iTilePlacement += l_iChanceDegridation; 


	}
}

void Grid::m_AssignTextures()
{
	if (m_GridMulti.size() > 0)
	{
		for (int i = 0; i < (int)m_GridMulti.size(); i++)
		{
			for (int j = 0; j < (int)m_GridMulti[i].size(); j++)
			{
				for (int k = 0; k < (int)m_GridMulti[i][j].size(); k++)
				{
					m_GridMulti[i][j][k].m_AssignTexture(); 
				}
			}
		}
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
