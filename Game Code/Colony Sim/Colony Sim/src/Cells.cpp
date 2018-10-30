/*! \file Cells.cpp
*
* This will hold all of the definitions for the class Cells.
*
*/

#include "../inc/Cells.h"

Cells::Cells()
{
}

Cells::~Cells()
{
}

void Cells::m_CreateCellBody(sf::Vector2f dimentions, sf::Vector2f possition)
{
	m_CellBody.setSize(dimentions); 

	m_SetObjectPos(possition.x, possition.y); 

	m_CellBody.setFillColor(sf::Color(255, 255, 255, 200)); 

	m_CellBody.setOutlineColor(sf::Color::Black);

	m_CellBody.setOutlineThickness(m_CellBody.getGlobalBounds().width * 0.01f); 
}

void Cells::m_CreateCellBody(sf::Vector2f dimentions, sf::Vector2f possition, int r, int g, int b)
{
	m_CellBody.setSize(dimentions);

	m_SetObjectPos(possition.x, possition.y);

	m_CellBody.setFillColor(sf::Color(r, g, b, 200));

	m_CellBody.setOutlineColor(sf::Color::Black);

	m_CellBody.setOutlineThickness(m_CellBody.getGlobalBounds().width * 0.01f);
}

void Cells::m_AssignCellId(int id)
{
	m_iCellId = id; 
}

int Cells::m_GetCellId()
{
	return m_iCellId;
}

void Cells::m_DrawGameObject(sf::RenderWindow & window)
{
	if (m_DrawItem == _DRAW)
	{
		window.draw(m_CellBody);
	} 
}

void Cells::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
	if (((m_CellBody.getPosition().x > topLeft.x) && (m_CellBody.getPosition().y > topLeft.y))
		&& ((m_CellBody.getPosition().x < bottomRight.x) && (m_CellBody.getPosition().y < bottomRight.y)))
	{
		m_DrawItem = _DRAW;
	}
	else
	{
		m_DrawItem = _NO_DRAW;
	}
}

void Cells::m_SetObjectPos(float x, float y)
{
	m_GameObjectPos = sf::Vector2f(x, y); 

	m_CellBody.setPosition(m_GameObjectPos); 
}
