#include "WoodPile.h"

WoodPile::WoodPile()
{
}

WoodPile::~WoodPile()
{
}

void WoodPile::m_InitWoodPile(Cells * pileLocation, sf::Font newFont, float currentGrowth)
{

	m_CurrentCell = pileLocation; 

	m_CurrentLayer = m_CurrentCell->m_GetLayer();

	// Create a max number of wood to generate dependng upon size of tree.

	int l_iMaxGeneratedWood = m_iMaxWood + currentGrowth; 

	m_iNumberOfWood = m_GenerateInt(l_iMaxGeneratedWood * 0.1f, l_iMaxGeneratedWood * 0.9f);

	// Create Main body for the pile of wood.
	m_PileBody.setSize(sf::Vector2f(10, 10));
	m_PileBody.setOrigin(m_PileBody.getGlobalBounds().width * 0.5f, m_PileBody.getGlobalBounds().height * 0.5f);
	m_PileBody.setFillColor(sf::Color::Magenta);
	m_PileBody.setOutlineColor(sf::Color::Black);
	m_PileBody.setOutlineThickness(m_PileBody.getGlobalBounds().width * 0.1f);

	// Create text element to display amount of wood. 
	m_CurrentFont = newFont;

	m_PileCount.setFont(m_CurrentFont); 

	m_PileCount.setString(std::to_string(m_iNumberOfWood));
	m_SetObjectPos(m_CurrentCell->m_GetCellCentre().x, m_CurrentCell->m_GetCellCentre().y);
	unsigned int l_iTextSize = 20;
	do
	{
		// Adjust text size to fit within mian body. 
		l_iTextSize -= 2; 
		m_PileCount.setCharacterSize(l_iTextSize);

	} while ((m_PileCount.getGlobalBounds().width > m_PileBody.getGlobalBounds().width) || 
		(m_PileCount.getGlobalBounds().height > m_PileBody.getGlobalBounds().height));

	m_PileCount.setFillColor(sf::Color::Black); 
}

void WoodPile::m_Update()
{
}

int WoodPile::m_TakeWood(int amountTaken)
{
	if (m_iNumberOfWood >= amountTaken)
	{

		m_iNumberOfWood -= amountTaken;

		std::cout << "Current Wood : " << m_iNumberOfWood << std::endl;

		m_PileCount.setString(std::to_string(m_iNumberOfWood));

		m_SetObjectPos(m_CurrentCell->m_GetCellCentre().x, m_CurrentCell->m_GetCellCentre().y);

		unsigned int l_iTextSize = 20;
		do
		{
			// Adjust text size to fit within mian body. 
			l_iTextSize -= 2;
			m_PileCount.setCharacterSize(l_iTextSize);

		} while ((m_PileCount.getGlobalBounds().width > m_PileBody.getGlobalBounds().width) ||
			(m_PileCount.getGlobalBounds().height > m_PileBody.getGlobalBounds().height));

	}
	else
	{
		amountTaken = m_iNumberOfWood; 

		m_iNumberOfWood = 0; 
	}

	if (m_iNumberOfWood <= 0)
	{
		m_bMarkForDeletion = true; 
	}

	return amountTaken; 
}

bool WoodPile::m_GetMarkForDeletion()
{
	return m_bMarkForDeletion;
}

void WoodPile::m_DrawGameObject(sf::RenderWindow & window)
{
	if (m_DrawItem == _DRAW)
	{
		window.draw(m_PileBody);

		if (m_PileCount.getFont() != nullptr)
		{
			m_PileCount.setFont(m_CurrentFont);

			window.draw(m_PileCount);
		}
	}

}

void WoodPile::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
	if (((m_PileBody.getPosition().x > topLeft.x) && (m_PileBody.getPosition().y > topLeft.y))
		&& ((m_PileBody.getPosition().x < bottomRight.x) && (m_PileBody.getPosition().y < bottomRight.y)))
	{
		m_DrawItem = _DRAW;
	}
	else
	{
		m_DrawItem = _NO_DRAW;
	}
}

void WoodPile::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, int currentLayer)
{
	if (m_CurrentLayer == currentLayer)
	{
		if (((m_PileBody.getPosition().x > topLeft.x) && (m_PileBody.getPosition().y > topLeft.y))
			&& ((m_PileBody.getPosition().x < bottomRight.x) && (m_PileBody.getPosition().y < bottomRight.y)))
		{
			m_DrawItem = _DRAW;
		}
		else
		{
			m_DrawItem = _NO_DRAW;
		}
	}
	else
	{
		m_DrawItem = _NO_DRAW;
	}
}

void WoodPile::m_SetObjectPos(float x, float y)
{
	m_GameObjectPos = sf::Vector2f(x, y); 

	m_PileBody.setPosition(x, y); 

	m_PileCount.setPosition(m_PileBody.getPosition().x - m_PileBody.getGlobalBounds().width * 0.5f,
		m_PileBody.getPosition().y - m_PileBody.getGlobalBounds().height * 0.5f);
}

Cells * WoodPile::m_GetCurentCell()
{
	if (this != nullptr)
	{
		return m_CurrentCell;
	}

	return nullptr; 
}

