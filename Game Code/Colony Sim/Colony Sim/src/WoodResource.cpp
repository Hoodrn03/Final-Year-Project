/*! \file WoodResource.cpp
*
* This will hold all of the definitions for the class WoodResource.
*
*/

#include "../inc/WoodResource.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
WoodResource::WoodResource()
{
}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
WoodResource::~WoodResource()
{
}

//--------------------------------------------------------
/*! \fn Create Tree : This will create a single tree for the game.
*Param One : float - The maximum radius for the tree.
*Param Two : vector2f - The position for the tree in the game world.
*Param Three : int - The layer the tree will be placed on.
*/
void WoodResource::m_CreateTree(float radius, sf::Vector2f position, int layer, Cells * newCurrentCell)
{
	m_fLargestRadius = radius; 

	m_fSmallestRadius = radius * 0.1f;

	m_iCurrentLayer = layer; 

	m_CurrentCell = newCurrentCell; 

	m_fCurrentGrowth = (float)m_GenerateInt((int)m_fSmallestRadius, (int)m_fLargestRadius); 

	m_TreeObject.setRadius(m_fCurrentGrowth); 

	m_TreeObject.setOrigin(sf::Vector2f(m_TreeObject.getGlobalBounds().width * 0.5f, m_TreeObject.getGlobalBounds().height * 0.5f));

	m_SetObjectPos(position.x, position.y);

	m_TreeObject.setFillColor(sf::Color::Green);

	m_TreeObject.setOutlineThickness(radius * 0.1f);

	m_TreeObject.setOutlineColor(sf::Color::Black); 
}

//--------------------------------------------------------
/*! \fn Update : This will be used to update the current tree.
*
*/
void WoodResource::m_Update()
{
	if (m_GrowthTimer.getElapsedTime().asSeconds() >= 50.f)
	{
		m_GrowthTimer.restart(); 

		// std::cout << "Update Tree" << std::endl;

		if (m_fCurrentGrowth < m_fLargestRadius)
		{
			m_fCurrentGrowth += m_fSmallestRadius; 
		}
		else if (m_fCurrentGrowth > m_fLargestRadius)
		{
			m_fCurrentGrowth = m_fLargestRadius; 
		}

		if (m_fCurrentGrowth != m_fPreveousRadius)
		{
			m_TreeObject.setRadius(m_fCurrentGrowth); 

			m_TreeObject.setRadius(m_fCurrentGrowth);

			m_TreeObject.setOrigin(sf::Vector2f(m_TreeObject.getGlobalBounds().width * 0.5f, m_TreeObject.getGlobalBounds().height * 0.5f));
			
			m_SetObjectPos(m_GetObjectPos().x, m_GetObjectPos().y);
		}

		m_fPreveousRadius = m_fCurrentGrowth; 
	}
}

//--------------------------------------------------------
/*! \fn DrawGameObject : This will allow for the connected class to draw the object onto the game window.
*Param One : RenderWindow - The current game window.
*/
void WoodResource::m_DrawGameObject(sf::RenderWindow & window)
{
	if (m_DrawItem == _DRAW)
	{
		window.draw(m_TreeObject);
	}
}

//--------------------------------------------------------
/*! \fn DrawFilter : This will be used to choose if the connected object should be drawn onto the game window.
*Param One : Vector2f - The top left of the game view, limiting the items drawn.
*Param Two : Vector2f - The bottom right of the game view, limiting the items drawn.
*/
void WoodResource::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
	if (((m_TreeObject.getPosition().x > topLeft.x) && (m_TreeObject.getPosition().y > topLeft.y))
		&& ((m_TreeObject.getPosition().x < bottomRight.x) && (m_TreeObject.getPosition().y < bottomRight.y)))
	{
		m_DrawItem = _DRAW;
	}
	else
	{
		m_DrawItem = _NO_DRAW;
	}
}

//--------------------------------------------------------
/*! \fn DrawFilter (Overload) : This will be used to choose if the connected object should be drawn onto the game window.
*Param One : Vector2f - The top left of the game view, limiting the items drawn.
*Param Two : Vector2f - The bottom right of the game view, limiting the items drawn.
*Param Three : int - The current layer for the tree, limits the draw to a single layer.
*/
void WoodResource::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, int currentLayer)
{
	if (currentLayer == m_iCurrentLayer)
	{
		if (((m_TreeObject.getPosition().x > topLeft.x) && (m_TreeObject.getPosition().y > topLeft.y))
			&& ((m_TreeObject.getPosition().x < bottomRight.x) && (m_TreeObject.getPosition().y < bottomRight.y)))
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

//--------------------------------------------------------
/*! \fn SetObjectPos : This will allow for the connected object to set the possition for the object.
*Param One : float - The X position for the game object.
*Param Two : float - The Y position for the game object.
*/
void WoodResource::m_SetObjectPos(float x, float y)
{
	m_GameObjectPos.x = x;
	m_GameObjectPos.y = y;

	m_TreeObject.setPosition(x, y);
}

Cells * WoodResource::m_GetCurrentCell()
{
	if (this == nullptr)
	{
		return nullptr;
	}

	return m_CurrentCell;
}

//--------------------------------------------------------
/*! \fn SetTreeCutDown : This will assign This tree to be cut down.
*
*/
void WoodResource::m_SetTreeCutDown()
{
	m_bCutDownTree = true; 
	
	m_TreeObject.setFillColor(sf::Color::Blue); 
}

void WoodResource::m_CancelTreeCutDown()
{
	m_bCutDownTree = false;

	m_TreeObject.setFillColor(sf::Color::Green);
}

bool WoodResource::m_GetTreeCutDown()
{
	return m_bCutDownTree;
}
