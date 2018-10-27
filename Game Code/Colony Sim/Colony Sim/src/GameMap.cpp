
#include "../inc/GameMap.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::m_SetUpGameMap(sf::Vector2f dimentions, sf::Vector2f position)
{
	m_MapObject.setSize(dimentions); 

	m_SetObjectPos(position.x, position.y); 

	m_MapObject.setFillColor(sf::Color::Green); 

}

void Map::m_DrawGameObject(sf::RenderWindow & window)
{
	window.draw(m_MapObject); 
}

void Map::m_SetObjectPos(float x, float y)
{
	m_GameObjectPos = sf::Vector2f(x, y); 

	m_MapObject.setPosition(m_GameObjectPos);
}
