
#include "../inc/Colonist.h"

Colonist::Colonist()
{
}

Colonist::~Colonist()
{
}

void Colonist::m_CreateColonistBody(sf::Vector2f dimentions, sf::Vector2f position)
{
	m_ColonistBody.setSize(dimentions);

	m_ColonistBody.setOrigin(sf::Vector2f(m_ColonistBody.getPosition().x + (m_ColonistBody.getGlobalBounds().width * 0.5f), 
		m_ColonistBody.getPosition().y + (m_ColonistBody.getGlobalBounds().height * 0.5f)));

	m_SetObjectPos(position.x, position.y); 

	m_ColonistBody.setFillColor(sf::Color::White); 

}

void Colonist::m_CreateColonistBody(sf::Vector2f dimentions, Cells * currentCell)
{
	m_ColonistBody.setSize(dimentions);

	m_ColonistBody.setOrigin(sf::Vector2f(m_ColonistBody.getPosition().x + (m_ColonistBody.getGlobalBounds().width * 0.5f),
		m_ColonistBody.getPosition().y + (m_ColonistBody.getGlobalBounds().height * 0.5f)));

	m_SetObjectPos(currentCell->m_GetCellCentre().x, currentCell->m_GetCellCentre().y);

	m_CurrentCell = currentCell; 

	m_ColonistBody.setFillColor(sf::Color::White);
}

void Colonist::m_Update()
{
	if (m_clPathfinding.m_CheckForCompletion() == false)
	{
		std::cout << "Running Algorithm" << std::endl;

		m_clPathfinding.m_RunAStarAlgorithm(); 
	}
	else
	{
		m_FollowPath(); 
	}
}

void Colonist::m_DrawGameObject(sf::RenderWindow & window)
{
	if (m_DrawItem == _DRAW)
	{
		window.draw(m_ColonistBody);
	}
}

void Colonist::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
	if ((m_GetObjectPos().x > topLeft.x && m_GetObjectPos().y > topLeft.y)
		&& (m_GetObjectPos().x < bottomRight.x && m_GetObjectPos().y < bottomRight.y))
	{
		m_DrawItem = _DRAW;
	}
	else
	{
		m_DrawItem = _NO_DRAW; 
	}

}

void Colonist::m_SetObjectPos(float x, float y)
{
	m_GameObjectPos = sf::Vector2f(x, y);

	m_ColonistBody.setPosition(m_GameObjectPos);
}

void Colonist::m_FollowPath()
{
	std::cout << "Following Path" << std::endl;

	if (m_clPathfinding.m_GetCurrentPath().size() > 0)
	{

	}
	else
	{
		// Todo :: find new path. 
	}
}

void Colonist::m_FindNewPath(Cells * endCell)
{
	m_clPathfinding.m_InitAlgorithm(m_CurrentCell, endCell);

	m_bFindNewPath = false;
}

bool Colonist::m_GetFindNewPath()
{
	return m_bFindNewPath;
}
