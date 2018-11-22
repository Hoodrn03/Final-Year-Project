

#include "../inc/ColonistManager.h"

ColonistManager::ColonistManager()
{
}

ColonistManager::~ColonistManager()
{
}

void ColonistManager::m_AddColonist(int numberOfColonists, sf::Vector2f dimentions, Grid & currentGrid, int startingLayer)
{
	int l_iNumberOfColonists = numberOfColonists;

	for (int i = 0; i < l_iNumberOfColonists; i++)
	{
		Colonist l_clColonist;

		l_clColonist.m_CreateColonistBody(sf::Vector2f(5, 5), currentGrid.m_GetRandomDirtCell(startingLayer));

		m_clColonists.push_back(l_clColonist);
	}
}

void ColonistManager::m_Update(Grid & CurrentGrid)
{
	if (m_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < m_clColonists.size(); i++)
		{
			m_clColonists[i].m_Update(); 

			m_clColonists[i].m_UpdateCurrentCell(CurrentGrid.m_ConvertWorldPosToGridPos(m_clColonists[i].m_GetObjectPos(), m_clColonists[i].m_GetCurrentLayer()));
		}
	}

}

void ColonistManager::m_Pathfinding(Grid & CurrentGrid)
{
	if (m_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < m_clColonists.size(); i++)
		{
			if (m_clColonists[i].m_GetFindNewPath() == true)
			{
				m_clColonists[i].m_FindNewPath(CurrentGrid.m_GetRandomDirtCell(m_clColonists[i].m_GetCurrentLayer())); 
			}
		}
	}
}

void ColonistManager::m_Render(sf::RenderWindow & window)
{
	if (m_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < m_clColonists.size(); i++)
		{
			m_clColonists[i].m_DrawGameObject(window); 
		}
	}
}

void ColonistManager::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
	if (m_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < m_clColonists.size(); i++)
		{
			m_clColonists[i].m_DrawFilter(topLeft, bottomRight); 
		}
	}
}

void ColonistManager::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, unsigned int currentLayer)
{
	if (m_clColonists.size() > 0)
	{
		for (unsigned int i = 0; i < m_clColonists.size(); i++)
		{
			m_clColonists[i].m_DrawFilter(topLeft, bottomRight, currentLayer);
		}
	}
}
