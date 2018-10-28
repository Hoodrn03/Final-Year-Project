#include "../inc/Grid.h"

Grid::Grid()
{
}

Grid::~Grid()
{
}

void Grid::m_CreateGrid(unsigned int rows, unsigned int columns, sf::RectangleShape gridLocation)
{
	float l_fCellWidth = gridLocation.getGlobalBounds().width / rows;
	float l_fCellHeight = gridLocation.getGlobalBounds().height / columns;

	sf::Vector2f l_CurrentCellPos = sf::Vector2f(gridLocation.getPosition());

	int l_iCurrentId = 0; 

	for (unsigned int i = 0; i < rows; i++)
	{
		std::vector<Cells> l_CurrentRow; 

		for (unsigned int j = 0; j < columns; j++)
		{
			Cells l_CurrentCell;

			l_CurrentCell.m_CreateCellBody(sf::Vector2f(l_fCellWidth, l_fCellHeight), l_CurrentCellPos);

			l_CurrentCell.m_AssignCellId(l_iCurrentId); 

			l_iCurrentId++; 

			l_CurrentCellPos += sf::Vector2f(0, l_fCellHeight); 

			l_CurrentRow.push_back(l_CurrentCell); 
		}

		m_Grid.push_back(l_CurrentRow); 

		l_CurrentCellPos += sf::Vector2f(l_fCellWidth, 0);

		l_CurrentCellPos.y = gridLocation.getPosition().y; 
	}

}

void Grid::m_DrawGrid(sf::RenderWindow & window)
{
	if (m_Grid.size() > 0)
	{
		for (unsigned int i = 0; i < m_Grid.size(); i++)
		{
			for (unsigned int j = 0; j < m_Grid[i].size(); j++)
			{
				m_Grid[i][j].m_DrawGameObject(window);
			}
		}
	}
}
