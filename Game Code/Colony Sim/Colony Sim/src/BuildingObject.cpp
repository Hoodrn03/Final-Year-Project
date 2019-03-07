#include "BuildingObject.h"

BuildingObject::BuildingObject()
{
}

BuildingObject::~BuildingObject()
{
}

void BuildingObject::m_SetupBuildingObject(sf::Vector2f dimentions, sf::Vector2f position)
{
	m_BuildingBody.setSize(dimentions); 
	m_BuildingBody.setOrigin(m_BuildingBody.getGlobalBounds().width * 0.5f, m_BuildingBody.getGlobalBounds().height * 0.5f);
	m_BuildingBody.setFillColor(sf::Color::Magenta); 

	m_SetObjectPos(position.x, position.y); 


}

void BuildingObject::m_Update()
{
}

void BuildingObject::m_DrawGameObject(sf::RenderWindow & window)
{
	window.draw(m_BuildingBody); 
}

void BuildingObject::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
}

void BuildingObject::m_SetObjectPos(float x, float y)
{
	m_BuildingBody.setPosition(x, y); 

	m_GameObjectPos = sf::Vector2f(x, y); 
}
