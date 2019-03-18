/*! \file This will hold all of the class definitions for the class Mouse.h. */

#include "../inc/Mouse.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
Mouse::Mouse()
{
	m_SelectionBox.setFillColor(sf::Color::Transparent); 

	m_SelectionBox.setOutlineThickness(1.f); 

	m_SelectionBox.setOutlineColor(sf::Color::Black);
}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
Mouse::~Mouse()
{
}

//--------------------------------------------------------
/*! \fn SetmousePos This will update the current mouse position.
*Param One : RenderWindow - The main game window.
*/
void Mouse::m_SetMousePos(sf::RenderWindow & window)
{
	// Get mouse position.
	sf::Vector2i l_PixelPos = sf::Mouse::getPosition(window);

	// Convert it to world coordinates.
	m_MousePos = window.mapPixelToCoords(l_PixelPos);
}

//--------------------------------------------------------
/*! \fn GetMousePos Used to return the value of the mouse position.
*
*/
sf::Vector2f Mouse::m_GetMousePos()
{
	return m_MousePos;
}

bool Mouse::m_GetLMBDown(sf::Vector2f mapUpperBounds, sf::Vector2f mapLowerBounds)
{
	if (((m_MousePos.x > mapUpperBounds.x) && (m_MousePos.y > mapUpperBounds.y)) && 
		((m_MousePos.x < mapLowerBounds.x) && (m_MousePos.y < mapLowerBounds.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return true; 
		}
	}

	return false;
}

void Mouse::m_CreateSelectionBox()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_bMouseFirstDown == false)
		{
			m_SelectionBox.setPosition(m_MousePos);

			m_bMouseFirstDown = true; 
		}
		else
		{
			float l_fHeight, l_fWidth;

			l_fWidth = m_MousePos.x - m_SelectionBox.getPosition().x;

			l_fHeight = m_MousePos.y - m_SelectionBox.getPosition().y;

			m_SelectionBox.setSize(sf::Vector2f(l_fWidth, l_fHeight)); 
		}
	}
	else
	{
		if (m_bMouseFirstDown != false)
		{
			m_bMouseFirstDown = false;

			m_SelectionBox.setSize(sf::Vector2f(0, 0)); 
		}
	}

}

void Mouse::m_DrawSelectionBox(sf::RenderWindow & window)
{
	window.draw(m_SelectionBox); 
}

void Mouse::m_AssignToolTipFont(sf::Font newFont)
{
	m_LocalFont = newFont;

	m_ToolTip.setFont(m_LocalFont);

	m_ToolTip.setFillColor(sf::Color::White);

	m_ToolTip.setOutlineColor(sf::Color::Black);

	m_ToolTip.setOutlineThickness(0.5f);
}

void Mouse::m_UpdateTooltip(std::string dataToDisplay, sf::Vector2f viewPos, sf::Vector2f viewSize)
{
	if (dataToDisplay != m_PreveousText)
	{
		m_ToolTip.setString(dataToDisplay);

		m_PreveousText = dataToDisplay;
	}

	m_ToolTip.setPosition(viewPos.x + (viewSize.x * 0.01f), viewPos.y + (viewSize.y * 0.90f));

	m_ToolTip.setCharacterSize(viewSize.y * 0.04f);
}

void Mouse::m_DrawToolTip(sf::RenderWindow & window)
{
	if (m_ToolTip.getFont() != nullptr)
	{
		window.draw(m_ToolTip); 
	}
}

sf::Vector2f Mouse::m_GetTopLeftSelectionBox()
{
	return m_SelectionBox.getPosition();
}

sf::Vector2f Mouse::m_GetBottomRightSelectionBox()
{
	return m_SelectionBox.getPosition() + m_SelectionBox.getSize();
}


