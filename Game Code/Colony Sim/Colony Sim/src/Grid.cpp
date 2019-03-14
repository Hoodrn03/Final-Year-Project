/*! \file Grid.cpp
*
* This will hold all of the definitions for the class Grid.
*
*/

#include "../inc/Grid.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
Grid::Grid()
{
}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
Grid::~Grid()
{
}

//--------------------------------------------------------
/*! \fn CreateGrid : This will be used to initalize the grid.
*Param One : int - The number of rows for the grid.
*Param Two : int - The number of columns for the grid.
*Param Three : int - The number of layers on the grid.
*Param Four : RectangleShape : The location and size for the grid, the grid is placed inside the rectangle shape.
*/
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

				l_CurrentCell.m_SetGridPos(j, k); 

				l_CurrentCell.m_SetLayer(i);

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

		m_Grid.push_back(l_Grid); 
	}

	m_AssignNeighbours(); 

}

//--------------------------------------------------------
/*! \fn AssignNeighbours : This will be used to give all of the cells within the grid their neighbours.
*
*/
void Grid::m_AssignNeighbours()
{
	if (m_Grid.size() > 0)
	{
		for (int i = 0; i < (int)m_Grid.size(); i++)
		{
			for (int j = 0; j < (int)m_Grid[i].size(); j++)
			{
				for (int k = 0; k < (int)m_Grid[i][j].size(); k++)
				{

					if (j - 1 >= 0)
					{
						// West Cell

						m_Grid[i][j][k].m_AssignNeighbour(m_Grid[i][j - 1][k]); 
					}

					if (k - 1 >= 0)
					{
						// North Cell

						m_Grid[i][j][k].m_AssignNeighbour(m_Grid[i][j][k - 1]);
					}

					if (j + 1 < (int)m_Grid[i].size())
					{
						// East Cell

						m_Grid[i][j][k].m_AssignNeighbour(m_Grid[i][j + 1][k]);
					}

					if (k + 1 < (int)m_Grid[i][j].size())
					{
						// South Cell

						m_Grid[i][j][k].m_AssignNeighbour(m_Grid[i][j][k + 1]);
					}

					if (k - 1 >= 0 && j - 1 >= 0)
					{
						// North West Cell

						m_Grid[i][j][k].m_AssignNeighbour(m_Grid[i][j - 1][k - 1]);
					}

					if (k - 1 >= 0 && j + 1 < (int)m_Grid[i].size())
					{
						// North East Cell

						m_Grid[i][j][k].m_AssignNeighbour(m_Grid[i][j + 1][k - 1]);
					}

					if (k + 1 < (int)m_Grid[i][j].size() && j - 1 >= 0)
					{
						// South West Cell

						m_Grid[i][j][k].m_AssignNeighbour(m_Grid[i][j - 1][k + 1]);
					}

					if (k + 1 < (int)m_Grid[i][j].size() && j + 1 < (int)m_Grid[i].size())
					{
						// South East Cell

						m_Grid[i][j][k].m_AssignNeighbour(m_Grid[i][j + 1][k + 1]);
					}

				}
			}
		}
	}
}

void Grid::m_AssignTextures(std::map<std::string, sf::Texture>& m_TextureMap)
{
	m_DirtTexture = m_TextureMap["grassOne"];

	m_WaterTexture = m_TextureMap["waterOne"];

	m_RockTexture = m_TextureMap["rockOne"]; 
}

//--------------------------------------------------------
/*! \fn CreateLake : This will be used to generate a lake within the grid.
*Param One : int - The x position of the start cell.
*Param Two : int - The y position of the start cell.
*Param Three : int - The layer which the lake should be generated.
*Param Four : int - The number of iterations the function should take while making the lake.
*/
void Grid::m_CreateLake(int cellX, int cellY, int layer, int numberOfIterations)
{
	// Local Variables. 

	int l_iTilePlacement = 10;

	int l_iChanceDegridation = 15; 

	int l_iTotalChance = numberOfIterations * l_iChanceDegridation;

	std::vector<Cells*> l_WaterTiles;

	std::vector<Cells*> l_CellsToAdd;

	// Set Start of lake. 

	m_Grid[layer][cellX][cellY].m_AssignTile(_WATER); 

	m_Grid[layer][cellX][cellY].m_AssignTexture(m_WaterTexture); 
	
	l_CellsToAdd.push_back(&m_Grid[layer][cellX][cellY]); 
 
	// Begin Lake Generation. 

	for (int i = 0; i < numberOfIterations; i++)
	{
		for (unsigned int j = 0; j < l_CellsToAdd.size(); j++)
		{
			// Loop throgh the neighbours of cells to add and add them into the water tiles. 

			for (unsigned int k = 0; k < l_CellsToAdd[j]->m_GetNeighbours().size(); k++)
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

		for (unsigned int j = 0; j < l_WaterTiles.size(); j++)
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
				l_WaterTiles[j]->m_AssignTile(_WATER);

				l_WaterTiles[j]->m_AssignTexture(m_WaterTexture);
			}

			for (unsigned int k = 0; k < l_WaterTiles[j]->m_GetNeighbours().size(); k++)
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

//--------------------------------------------------------
/*! \fn CreateRiver : This will be used to create a river in the grid.
*Param One : Vector<Cells> - A path of cells the river should be generated along.
*Param Two : int - The width in cells the river should be.
*Param Three : int - The layer the river should be generated on.
*/
void Grid::m_CreateRiver(std::deque<Cells*> riverPath, int riverWidth, int layer)
{
	for (unsigned int i = 0; i < riverPath.size(); i++)
	{
		for (int j = 0; j < riverWidth; j++)
		{
			if (riverPath[i]->m_GetGridPos().x + j < m_Grid[layer].size())
			{
				m_Grid[layer][(unsigned int)riverPath[i]->m_GetGridPos().x + j][(unsigned int)riverPath[i]->m_GetGridPos().y].m_AssignTile(_WATER);

				m_Grid[layer][(unsigned int)riverPath[i]->m_GetGridPos().x + j][(unsigned int)riverPath[i]->m_GetGridPos().y].m_AssignTexture(m_WaterTexture);
			}

			if (riverPath[i]->m_GetGridPos().y + j < m_Grid[layer][0].size())
			{
				m_Grid[layer][(unsigned int)riverPath[i]->m_GetGridPos().x][(unsigned int)riverPath[i]->m_GetGridPos().y + j].m_AssignTile(_WATER);

				m_Grid[layer][(unsigned int)riverPath[i]->m_GetGridPos().x + j][(unsigned int)riverPath[i]->m_GetGridPos().y].m_AssignTexture(m_WaterTexture);
			}
		}
	}

}

//--------------------------------------------------------
/*! \fn Create Underground Water : This will be used to create water for layers under the gound level.
*Param One : int - The lowest layer for the water to be placed on.
*Param Two : int - The highest layer for the water to be placed on.
*/
void Grid::m_CreateUndergroundWater(int minLayer, int maxLayer)
{
	const int l_iWaterPlacement = 30; 

	std::cout << l_iWaterPlacement << std::endl;

	for (int i = maxLayer; i >= minLayer; i--)
	{
		for (unsigned int j = 0; j < m_Grid[i].size(); j++)
		{
			for (unsigned int k = 0; k < m_Grid[i][j].size(); k++)
			{
				if (m_Grid[i + 1][j][k].m_GetTile() == _WATER)
				{
					if (m_GenerateInt(0, 100) <= l_iWaterPlacement)
					{
						m_Grid[i][j][k].m_AssignTile(_WATER);

						m_Grid[i][j][k].m_AssignTexture(m_WaterTexture); 
					}
				}
			}
		}
	}
}

//--------------------------------------------------------
/*! \fn Create Rock : This will be used to assign cells to be rock tiles.
*Param One : int - Which layer on the map the rock should be assigned to.
*/
void Grid::m_CreateRock(int layer)
{
	const int l_iRockPlacement = 5; 

	const int l_iAdjacentBoost = 20;

	int l_iAdjacentBonus = 0;

	for (unsigned int i = 0; i < m_Grid[layer].size(); i++)
	{
		for (unsigned int j = 0; j < m_Grid[layer][i].size(); j++)
		{
			if (m_Grid[layer][i][j].m_GetTile() != _NO_VALUE)
			{
				
			}
			else
			{
				for (unsigned int k = 0; k < m_Grid[layer][i][j].m_GetNeighbours().size(); k++)
				{
					if (m_Grid[layer][i][j].m_GetNeighbours()[k]->m_GetTile() == _ROCK)
					{
						l_iAdjacentBonus += l_iAdjacentBoost; 
					}
				}

				if (m_GenerateInt(0, 100) <= (l_iRockPlacement + l_iAdjacentBonus))
				{
					m_Grid[layer][i][j].m_AssignTile(_ROCK);

					m_Grid[layer][i][j].m_AssignTexture(m_RockTexture); 
				}
			}
			
			l_iAdjacentBonus = 0; 

		}
	}
}

//--------------------------------------------------------
/*! \fn Create Underground Rock : This will create rock for layers under the ground level.
*Param One : int - The lowest layer for the rock to be placed on.
*Param Two : int - The highest layer for the rock to be placed on.
*/
void Grid::m_CreateUndergroundRock(int minLayer, int maxLayer)
{
	const int l_iRockPlacement = 90;

	int l_iUpdatedChance = 0; 

	const int l_iDecreaseChance = 5;

	for (int i = maxLayer; i >= minLayer; i--)
	{
		for (unsigned int j = 0; j < m_Grid[i].size(); j++)
		{
			for (unsigned int k = 0; k < m_Grid[i][j].size(); k++)
			{
				if (m_Grid[i][j][k].m_GetTile() == _NO_VALUE)
				{
					if (m_GenerateInt(0, 100) <= l_iRockPlacement + l_iUpdatedChance)
					{
						m_Grid[i][j][k].m_AssignTile(_ROCK);

						m_Grid[i][j][k].m_AssignTexture(m_RockTexture);
					}
				}
			}
		}

		l_iUpdatedChance += l_iDecreaseChance; 
	}
}

//--------------------------------------------------------
/*! \fn Create Upper Rock : This will be used to create rock cells above the ground level.
*Param One : int - The lowest layer for the rock to be placed on.
*Param Two : int - The highest layer for the rock to be placed on.
*/
void Grid::m_CreateUpperRock(int minLayer, int maxLayer)
{
	const int l_iRockPlacement = 60;

	const int l_iDecreaseAmount = 20; 

	int l_iDecreasedChance = 0; 
	
	for (int i = minLayer; i <= maxLayer; i++)
	{
		for (unsigned int j = 0; j < m_Grid[i].size(); j++)
		{
			for (unsigned int k = 0; k < m_Grid[i][j].size(); k++)
			{
				if (m_Grid[i - 1][j][k].m_GetTile() == _ROCK)
				{
					if (m_GenerateInt(0, 100) <= (l_iRockPlacement - l_iDecreasedChance))
					{
						m_Grid[i][j][k].m_AssignTile(_ROCK);

						m_Grid[i][j][k].m_AssignTexture(m_RockTexture);
					}
				}
			}
		}

		l_iDecreasedChance += l_iDecreaseAmount;
	}
}

//--------------------------------------------------------
/*! \fn Create Dirt : This will fill in the remaning tiles on the map with dirt, used last in the generation process.
*Param One : int - Which layer on the map the dirt should be assigned to.
*/
void Grid::m_CreateDirt(int layer)
{
	for (unsigned int i = 0; i < m_Grid[layer].size(); i++)
	{
		for (unsigned int j = 0; j < m_Grid[layer][i].size(); j++)
		{
			if (m_Grid[layer][i][j].m_GetTile() != _NO_VALUE)
			{

			}
			else
			{
				m_Grid[layer][i][j].m_AssignTile(_DIRT);

				m_Grid[layer][i][j].m_AssignTexture(m_DirtTexture); 
			}
		}
	}
}

//--------------------------------------------------------
/*! \fn Create Underground Dirt : This will be used to fill the remaning underground tiles with dirt.
*Param One : int - The lowest layer for the dirt to be placed on.
*Param Two : int - The highest layer for the dirt to be placed on.
*/
void Grid::m_CreateUndergroundDirt(int minLayer, int maxLayer)
{
	for (int i = maxLayer; i >= minLayer; i--)
	{
		for (unsigned int j = 0; j < m_Grid[i].size(); j++)
		{
			for (unsigned int k = 0; k < m_Grid[i][j].size(); k++)
			{
				if (m_Grid[i][j][k].m_GetTile() != _NO_VALUE)
				{

				}
				else
				{
					m_Grid[i][j][k].m_AssignTile(_DIRT);

					m_Grid[i][j][k].m_AssignTexture(m_DirtTexture);
				}
			}
		}
	}
}

//--------------------------------------------------------
/*! \fn Create Sky : This will be used to fill the remaning above ground tiles with sky tiles.
*Param One : int - The lowest layer for the sky to be placed on.
*Param Two : int - The highest layer for the sky to be placed on.
*/
void Grid::m_CreateSky(int minLayer, int maxLayer)
{
	for (int i = minLayer; i <= maxLayer; i++)
	{
		for (unsigned int j = 0; j < m_Grid[i].size(); j++)
		{
			for (unsigned int k = 0; k < m_Grid[i][j].size(); k++)
			{
				if (m_Grid[i][j][k].m_GetTile() == _NO_VALUE)
				{
					m_Grid[i][j][k].m_AssignTile(_SKY);
				}
			}
		}
	}
}

//--------------------------------------------------------
/*! \fn GetCell : This will be used to get access to a specific cell.
*Param One : int - The layer of the cell.
*Param Two : int - The X for the cell.
*Param Three : int - The Y for the cell.
*/
Cells * Grid::m_GetCell(int layer, int x, int y)
{
	return &m_Grid[layer][x][y];
}

//--------------------------------------------------------
/*! \fn GetRandomDirtCell : This will be used to return a reference to a randomly selected cell with the tile code of dirt.
*Param One : int - Which layer to get the tile from.
*/
Cells * Grid::m_GetRandomDirtCell(int layer)
{
	Cells * l_ReturnValue;

	do
	{
		l_ReturnValue = &m_Grid[layer][m_GenerateInt(0, m_GetNumberOfRows())][m_GenerateInt(0, m_GetNumberOfColumns())];


	} while (l_ReturnValue->m_GetTile() != _DIRT);

	return l_ReturnValue;
}

//--------------------------------------------------------
/*! \fn ConvertWoldPosToGridPos : This will be used to convert world coordinates in the game window to a tile cell on the grid.
*Param One : Vector2f - The position in wold space to convert.
*/
Cells * Grid::m_ConvertWorldPosToGridPos(sf::Vector2f currentPos, unsigned int layer)
{
	Cells * l_ReturnValue;
	for (unsigned int j = 0; j < m_Grid[layer].size(); j++)
	{
		for (unsigned int k = 0; k < m_Grid[layer][j].size(); k++)
		{
			if (m_Grid[layer][j][k].m_CheckCellBounds(currentPos.x, currentPos.y))
			{
				l_ReturnValue = &m_Grid[layer][j][k];

				return l_ReturnValue;
			}
		}
	}

	// std::cout << "Unable to find cell" << std::endl;

	return nullptr;
}

//--------------------------------------------------------
/*! \fn DrawGrid : This will be used to draw the grid.
*Param One : renderwindow - The main game window the grid should be drawn onto.
*Param Two : int - The layer of the grid to be drawn.
*/
void Grid::m_DrawGrid(sf::RenderWindow & window, unsigned int layer)
{
	if (m_Grid.size() > layer)
	{
		for (unsigned int i = 0; i < m_Grid[layer].size(); i++)
		{
			for (unsigned int j = 0; j < m_Grid[layer][i].size(); j++)
			{
				m_Grid[layer][i][j].m_DrawGameObject(window);
			}
		}
	}
}

//--------------------------------------------------------
/*! \fn CheckItemsForRender : This will be used to limit the items to be drawn.
*Param One : vector2f - The top left of the view.
*Param Two : vector2f - The bottom right of the view.
*Param Three : int - The layer of items to draw.
*/
void Grid::m_CheckItemsForRender(sf::Vector2f topLeft, sf::Vector2f bottomRight, unsigned int layer)
{
	if (m_Grid.size() > 0)
	{
		for (unsigned int i = 0; i < m_Grid[layer].size(); i++)
		{
			for (unsigned int j = 0; j < m_Grid[layer][i].size(); j++)
			{
				m_Grid[layer][i][j].m_DrawFilter(topLeft, bottomRight);
			}
		}
	}
}

//--------------------------------------------------------
/*! \fn GetNumberOfLayers : This will be used to check the number of layers on the grid.
*
*/
unsigned int Grid::m_GetNumberOfLayers()
{
	if (m_Grid.size() > 0)
	{
		int l_ReturnValue = m_Grid.size();

		return l_ReturnValue;
	}
	else
	{
		return NULL; 
	}
}

//--------------------------------------------------------
/*! \fn GetNumberOfRows : This will be used to check the number of rows on the grid.
*
*/
unsigned int Grid::m_GetNumberOfRows()
{
	if (m_Grid[0].size() > 0)
	{
		int l_ReturnValue = m_Grid[0].size();

		return l_ReturnValue;
	}
	else
	{
		return NULL;
	}
}

//--------------------------------------------------------
/*! \fn GetNumberOfColumns : This will be used to check the number of columns on the grid.
*
*/
unsigned int Grid::m_GetNumberOfColumns()
{
	if (m_Grid[0][0].size() > 0)
	{
		int l_ReturnValue = m_Grid[0][0].size();

		return l_ReturnValue;
	}
	else
	{
		return NULL;
	}
}
