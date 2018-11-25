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
int Colonist::m_CreateColonistBody(sf::Vector2f dimentions, Cells * currentCell)
{
	try
	{
		if (currentCell != nullptr)
		{
			m_ColonistBody.setSize(dimentions);

			m_ColonistBody.setOrigin(sf::Vector2f(m_ColonistBody.getPosition().x + (m_ColonistBody.getGlobalBounds().width * 0.5f),
				m_ColonistBody.getPosition().y + (m_ColonistBody.getGlobalBounds().height * 0.5f)));

			m_SetObjectPos(currentCell->m_GetCellCentre().x, currentCell->m_GetCellCentre().y);

			m_SetCurrentLayer(currentCell->m_GetLayer()); 

			m_CurrentCell = currentCell;

			m_ColonistBody.setFillColor(sf::Color::White);
		}
		else
		{
			throw 42;
		}
	}
	catch (int)
	{
		// If a nullptr is passed into this function it will exit with an error. 

		return 1;
	}

	return 0; 
}

//--------------------------------------------------------
/*! \fn Update Current Cell : This will be used to assign the colonist a new current cell.
*Param One : Cells - This will be the new value for the current cell.
*/
void Colonist::m_UpdateCurrentCell(Cells * newCurrentCell)
{
	if (newCurrentCell != nullptr)
	{
		m_CurrentCell = newCurrentCell;
	}
}

//--------------------------------------------------------
/*! \fn Update : This will be used to update the logic for this class.
*
*/
void Colonist::m_Update()
{
	if (m_bFindNewPath != true)
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
		if (m_PathLine.getVertexCount() > 0)
		{
			window.draw(m_PathLine); 
		}

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
	if (((m_ColonistBody.getPosition().x > topLeft.x) && (m_ColonistBody.getPosition().y > topLeft.y))
		&& ((m_ColonistBody.getPosition().x < bottomRight.x) && (m_ColonistBody.getPosition().y < bottomRight.y)))
	{
		m_DrawItem = _DRAW;
	}
	else
	{
		m_DrawItem = _NO_DRAW; 
	}

}

//--------------------------------------------------------
/*! \fn Draw Filter (Overload) : This will be used to filter this object for draing, used to limit the amount drawn onto the screen at a given time.
*Param One : Vector2f - The top left corner of the game view.
*Param Two : Vector2f - The bottom right corner of the game view.
*Param Three : unsinged int - The current layer the displayed on the game window.
*/
void Colonist::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, unsigned int currentLayer)
{
	if (m_iCurrentLayer == currentLayer)
	{
		if (((m_ColonistBody.getPosition().x > topLeft.x) && (m_ColonistBody.getPosition().y > topLeft.y))
			&& ((m_ColonistBody.getPosition().x < bottomRight.x) && (m_ColonistBody.getPosition().y < bottomRight.y)))
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
/*! \fn Set Current Layer : This will be used to set the colonist's current layer on the map.
*Param One : unsigned int - The new layer the colonist is on.
*/
void Colonist::m_SetCurrentLayer(unsigned int newLayer)
{
	m_iCurrentLayer = newLayer;
}

//--------------------------------------------------------
/*! \fn Get Current Layer : THis will return the value for the current layer which the colonist is on.
*
*/
int Colonist::m_GetCurrentLayer()
{
	return m_iCurrentLayer;
}

//--------------------------------------------------------
/*! \fn Follow Path : This will be used to move the colonist along the new found path.
*
*/
void Colonist::m_FollowPath()
{
	if (m_Path.size() > 0)
	{
		if (m_MovementClock.getElapsedTime().asSeconds() >= m_fmovementTimer)
		{
			m_MovementClock.restart(); 

			if (m_iCurrentMoveTo < m_Path.size())
			{
				m_SetObjectPos(m_Path[m_iCurrentMoveTo]->m_GetCellCentre().x, m_Path[m_iCurrentMoveTo]->m_GetCellCentre().y);

				m_CreatePathLine(m_iCurrentMoveTo);

				m_iCurrentMoveTo++;
			}
			else
			{
				// Reached the end of the path. 

				m_iCurrentMoveTo = 0;

				m_Path.clear();

				m_PathLine.clear(); 

				m_bFindNewPath = true;
			}
		}
	} 
}

//--------------------------------------------------------
/*! \fn Find New Path : This will initalize a new path for the colonist.
*Param One : Cells - This will be the new end cell for the colonist.
*/
int Colonist::m_FindNewPath(Cells * endCell)
{
	try
	{
		int l_numberOfLoop = 0;

		if ((endCell != nullptr) && (m_CurrentCell != nullptr))
		{
			// std::cout << "Findng New Path" << std::endl;

			m_Path.clear();

			if (m_CurrentCell->m_GetLayer() == endCell->m_GetLayer())
			{

				do
				{

					Pathfinding l_clPathfinding;

					l_clPathfinding.m_InitAlgorithm(m_CurrentCell, endCell);

					do
					{
						l_clPathfinding.m_RunAStarAlgorithm(m_Obstructions);

						l_numberOfLoop++;

						if (l_numberOfLoop >= LOOP_TIMEOUT)
						{
							throw 3;
						}

					} while (l_clPathfinding.m_CheckForCompletion() == false);

					for (unsigned int i = 0; i < l_clPathfinding.m_GetCurrentPath().size(); i++)
					{
						m_Path.push_front(l_clPathfinding.m_GetCurrentPath()[i]);

						// std::cout << "Adding path to vector" << std::endl;

						l_numberOfLoop++;

						if (l_numberOfLoop >= LOOP_TIMEOUT)
						{
							throw 3;
						}
					}

					if (m_Path.size() >= 0)
					{
						m_bFindNewPath = false;
					}

					l_numberOfLoop++;

					if (l_numberOfLoop >= LOOP_TIMEOUT)
					{
						throw 3;
					}

				} while (m_bFindNewPath == true);
			}
			else
			{
				throw 42;
			}
		}
	}
	catch (int i)
	{
		switch(i)
		{
		case 3:
			// This will timeout the function. 
			return 1;
			break;

		case 42:
			// If the function attempts to access a nullptr it will exit. 
			return 1;
			break;

		default:
			std::cout << "Unable to Perform Function : Error Code : " << i << std::endl;
			return 1; 
			break;
		}
	}

	return 0; 
}

//--------------------------------------------------------
/*! \fn Get Find New Path : This will determine if a new path should be generated for the colonist.
*
*/
bool Colonist::m_GetFindNewPath()
{
	return m_bFindNewPath;
}

void Colonist::m_CreatePathLine(int currentPos)
{
	m_PathLine.clear(); 

	m_PathLine.setPrimitiveType(sf::LineStrip); 

	for (unsigned int i = currentPos; i < m_Path.size(); i++)
	{
		m_PathLine.append(m_Path[i]->m_GetCellCentre()); 
	}
}
