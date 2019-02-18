#include "WoodPile.h"

WoodPile::WoodPile()
{
}

WoodPile::~WoodPile()
{
}

void WoodPile::m_InitWoodPile(Cells * pileLocation, sf::Font newFont, float currentGrowth)
{

	m_iNumberOfWood = m_GenerateInt(m_iMaxWood * 0.1f, m_iMaxWood * 0.9f);

	std::cout << m_iNumberOfWood << std::endl;

	m_PileBody.setSize(sf::Vector2f(50, 50));
	m_PileBody.setOrigin(m_PileBody.getGlobalBounds().width * 0.5f, m_PileBody.getGlobalBounds().height * 0.5f);
	m_PileBody.setFillColor(sf::Color::Magenta);
	m_PileBody.setOutlineColor(sf::Color::Black);
	m_PileBody.setOutlineThickness(m_PileBody.getGlobalBounds().width * 0.1f);

	m_CurrentFont = newFont;

	m_PileCount.setFont(m_CurrentFont); 
	m_PileCount.setCharacterSize(m_PileBody.getGlobalBounds().height * 0.5f);
	m_PileCount.setPosition(m_PileBody.getPosition().x - m_PileBody.getGlobalBounds().width * 0.5f, 
		m_PileBody.getPosition().y - m_PileBody.getGlobalBounds().height * 0.5f); 
	m_PileCount.setString(std::to_string(m_iNumberOfWood));
	m_PileCount.setFillColor(sf::Color::Black); 

}

void WoodPile::m_Update()
{
}

void WoodPile::m_DrawGameObject(sf::RenderWindow & window)
{
	window.draw(m_PileBody); 
	
	if (m_PileCount.getFont() != NULL)
	{
		window.draw(m_PileCount); 
	}
}

void WoodPile::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
}

void WoodPile::m_SetObjectPos(float x, float y)
{
}

sf::Vector2f WoodPile::m_GetObjectPos()
{
	return sf::Vector2f();
}
