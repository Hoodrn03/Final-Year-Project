
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

void Colonist::m_Update()
{
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
