/*! \file Colonist.cpp
*
* This will hold all of the definitions for the class Colonist.
*
*/

#include "../inc/Colonist.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
Colonist::Colonist()
{
}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
Colonist::~Colonist()
{
}

//--------------------------------------------------------
/*! \fn Create Colonist Body : This will be used to initalize the rectangle shape dor what will become the colonist.
*Param One : Vector2f - This will be the dimentions for the colonist.
*Param Two : Vector2f - This Will be the position in world space for the colonist.
*/
void Colonist::m_CreateColonistBody(sf::Vector2f dimentions, sf::Vector2f position)
{
	m_ColonistBody.setSize(dimentions);

	m_ColonistBody.setOrigin(sf::Vector2f(m_ColonistBody.getPosition().x + (m_ColonistBody.getGlobalBounds().width * 0.5f), 
		m_ColonistBody.getPosition().y + (m_ColonistBody.getGlobalBounds().height * 0.5f)));

	m_SetObjectPos(position.x, position.y); 

	m_ColonistBody.setFillColor(sf::Color::White); 

}

//--------------------------------------------------------
/*! \fn Create Colonist Body (Overload) : This will be used to initalize the rectangle shape dor what will become the colonist.
*Param One : Vector2f - This will be the dimentions for the colonist.
*Param Two : Cells - The cell the colonist will start in.
*/
void Colonist::m_CreateColonistBody(sf::Vector2f dimentions, Cells * currentCell)
{
	m_ColonistBody.setSize(dimentions);

	m_ColonistBody.setOrigin(sf::Vector2f(m_ColonistBody.getPosition().x + (m_ColonistBody.getGlobalBounds().width * 0.5f),
		m_ColonistBody.getPosition().y + (m_ColonistBody.getGlobalBounds().height * 0.5f)));

	m_SetObjectPos(currentCell->m_GetCellCentre().x, currentCell->m_GetCellCentre().y);

	m_CurrentCell = currentCell; 

	m_ColonistBody.setFillColor(sf::Color::White);
}

//--------------------------------------------------------
/*! \fn Update : This will be used to update the logic for this class.
*
*/
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

//--------------------------------------------------------
/*! \fn Draw Game Object : This will be used to render the colonist.
*Param One : RenderWindow - The current game widow for the object to be drawn onto.
*/
void Colonist::m_DrawGameObject(sf::RenderWindow & window)
{
	if (m_DrawItem == _DRAW)
	{
		window.draw(m_ColonistBody);
	}
}

//--------------------------------------------------------
/*! \fn Draw Filter : This will be used to filter this object for draing, used to limit the amount drawn onto the screen at a given time.
*Param One : Vector2f - The top left corner of the game view.
*Param Two : Vector2f - The bottom right corner of the game view.
*/
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

//--------------------------------------------------------
/*! \fn Set Object Pos : This will be used to update the current position of the game object.
*Param One : float - The new X for the object.
*Param Two : float - The new Y for the object.
*/
void Colonist::m_SetObjectPos(float x, float y)
{
	m_GameObjectPos = sf::Vector2f(x, y);

	m_ColonistBody.setPosition(m_GameObjectPos);
}

//--------------------------------------------------------
/*! \fn Follow Path : This will be used to move the colonist along the new found path.
*
*/
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

//--------------------------------------------------------
/*! \fn Find New Path : This will initalize a new path for the colonist.
*Param One : Cells - This will be the new end cell for the colonist.
*/
void Colonist::m_FindNewPath(Cells * endCell)
{
	m_clPathfinding.m_InitAlgorithm(m_CurrentCell, endCell);

	m_bFindNewPath = false;
}

//--------------------------------------------------------
/*! \fn Get Find New Path : This will determine if a new path should be generated for the colonist.
*
*/
bool Colonist::m_GetFindNewPath()
{
	return m_bFindNewPath;
}
