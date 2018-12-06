#include "..\inc\ResourceManagement.h"

ResourceManagement::ResourceManagement()
{
}

ResourceManagement::~ResourceManagement()
{
}

void ResourceManagement::m_AddTrees(int numberOfTrees, float maxRadius, int layer, Grid & grid)
{
	for (int i = 0; i < numberOfTrees; i++)
	{
		WoodResource l_TempTree; 

		l_TempTree.m_CreateTree(maxRadius, grid.m_GetRandomDirtCell(layer)->m_GetCellCentre(), layer); 

		m_Trees.push_back(l_TempTree);
	}
}

void ResourceManagement::m_DrawTrees(sf::RenderWindow & window)
{
	if (m_Trees.size() > 0)
	{
		for (unsigned int i = 0; i < m_Trees.size(); i++)
		{
			m_Trees[i].m_DrawGameObject(window); 
		}
	}
}

void ResourceManagement::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
	if (m_Trees.size() > 0)
	{
		for (unsigned int i = 0; i < m_Trees.size(); i++)
		{
			m_Trees[i].m_DrawFilter(topLeft, bottomRight); 
		}
	}
}

void ResourceManagement::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, int currentLayer)
{
	if (m_Trees.size() > 0)
	{
		for (unsigned int i = 0; i < m_Trees.size(); i++)
		{
			m_Trees[i].m_DrawFilter(topLeft, bottomRight, currentLayer);
		}
	}
}

void ResourceManagement::m_Update()
{
	if (m_Trees.size() > 0)
	{
		for (unsigned int i = 0; i < m_Trees.size(); i++)
		{
			m_Trees[i].m_Update();
		}
	}
}


