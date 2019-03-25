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

			m_SelectedCircle.setRadius(dimentions.x);

			m_SelectedCircle.setFillColor(sf::Color::Blue);

			m_clInfoWindow.m_SetupInfoWindow(sf::Vector2f(100, 100), sf::Vector2f(100, 100));

			// Initalize paired values. 

			m_SleepData = std::make_pair(std::string("Sleep"), 100);

			m_HealthData = std::make_pair(std::string("Health"), 100);
		}
		else
		{
			throw 42;
		}
	}
	catch (int)
	{
		// If a nullptr is passed into This function it will exit with an error. 

		return 1;
	}

	return 0; 
}

void Colonist::m_AssignColonistFont(sf::Font &newFont)
{
	m_LocalFont = newFont;

	m_clInfoWindow.m_AssignFonts(m_LocalFont);

	// Pass into info window. 

	m_clInfoWindow.m_AddDataToMap(m_HealthData.first, m_HealthData.second);

	m_clInfoWindow.m_AddDataToMap(m_SleepData.first, m_SleepData.second);
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
/*! \fn Update : This will be used to update the logic for This class.
*
*/
void Colonist::m_Update()
{
	m_UpdateCondition(); 

	// At the beginning of the frame the colonist's current pasition will be updated. 
	if (m_bFindNewPath != true)
	{
		m_FollowPath();
	}

	if (m_SleepData.second <= 50)
	{
		std::cout << "Need Sleep" << std::endl;

		m_bNeedSleep = true; 
	}
	else 
	{

		// This will be used to allow for the colonists to interact with items based on their current job. 
		switch (m_CurrentJob)
		{

		case _IDLE:

			// If the colonist has no other job This is the base job. 
			m_IdleJob();

			break;

		case _LOGGING:

			m_CutTrees();

			break;

		case _CONSTRUCTION:

			m_BuildBuilding();

			break;

		default:

			// If the colonist has no other job This is the base job. 
			m_IdleJob();
			break;
		}
	}
}

void Colonist::m_UpdateInfoWindow(sf::Vector2f viewLowerBounds, sf::Vector2f viewSize)
{
	m_clInfoWindow.m_UpdateInfoWindow(viewLowerBounds, viewSize); 
}

void Colonist::m_UpdateCondition()
{
	int l_iConditionUpdateTime = 5; 

	if (m_ConditionTimer.getElapsedTime().asSeconds() >= l_iConditionUpdateTime)
	{
		m_ConditionTimer.restart();

		if (m_bAtInteratableObject() == true)
		{
			if (m_InteractableObject->m_GetBuildingType() == "Bed")
			{
				m_SleepData.second += 2;

				if (m_SleepData.second >= 80)
				{
					m_bNeedSleep = false; 

					if (m_SleepData.second > 100)
					{
						m_SleepData.second = 100;
					}
				}
			}
		}
		else
		{
			m_SleepData.second -= 1;

			if (m_SleepData.second <= 0)
			{
				m_SleepData.second = 0;

				m_HealthData.second -= 1;
			}

		}

		m_clInfoWindow.m_AddDataToMap(m_HealthData.first, m_HealthData.second);

		m_clInfoWindow.m_AddDataToMap(m_SleepData.first, m_SleepData.second);
	}
}

void Colonist::m_SetJob(job newJob)
{
	m_CurrentJob = newJob; 
}

//--------------------------------------------------------
/*! \fn Idle Job : A job for the colonist without them actually doing anything.
*
*/
void Colonist::m_IdleJob()
{
	// todo - When recreational objects are added add functionality to interact with them here. 

	// If not working keep the timer at 0. 
	m_WorkTimer.restart(); 
}

void Colonist::m_CutTrees()
{
	// Cut down tree

	if (m_AtTargetTree() == true)
	{
		if (m_WorkTimer.getElapsedTime().asSeconds() >= 1.f)
		{
			m_WorkTimer.restart();

			m_TargetTree->m_SetMarkForDeletion(true);
		}
	}
	else
	{
		m_WorkTimer.restart();
	}
}

void Colonist::m_BuildBuilding()
{
	if (m_AtTargetBuild() == true)
	{

		if (m_WorkTimer.getElapsedTime().asSeconds() >= 1.f)
		{
			m_WorkTimer.restart();

			if (m_TargetBuild->m_NeedWood() == true)
			{
				m_iNeededWood = m_TargetBuild->m_GetWoodNeeded(); 

				std::cout << "Need Wood" << std::endl;

				if (m_iCurrentWood > 0)
				{
					m_TargetBuild->m_AddWoodToBuilding(m_iCurrentWood);

					m_iCurrentWood = 0;

					m_iNeededWood = 0; 

					std::cout << "Added Wood" << std::endl;
				}
			}
			else 
			{
				m_TargetBuild->m_WorkBuilding(5);

				if (m_TargetBuild->m_bFinishedBuilding == true)
				{
					for (unsigned int i = 0; i < m_TargetBuild->m_GetCurrentCell()->m_GetNeighbours().size(); i++)
					{
						if (m_TargetBuild->m_GetCurrentCell()->m_GetNeighbours()[i]->m_GetTile() == _DIRT)
						{
							m_SetObjectPos(m_TargetBuild->m_GetCurrentCell()->m_GetNeighbours()[i]->m_GetCellCentre().x,
								m_TargetBuild->m_GetCurrentCell()->m_GetNeighbours()[i]->m_GetCellCentre().y);
						}
					}

					m_TargetBuild = nullptr;
				}
			}
		}
	}
	else
	{
		m_WorkTimer.restart();
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
		if (m_bSelected)
		{
			window.draw(m_SelectedCircle);
		}

		if (m_PathLine.getVertexCount() > 0)
		{
			window.draw(m_PathLine);
		}

		window.draw(m_ColonistBody);
	}

	m_clInfoWindow.m_DrawInfoWindow(window);
}

//--------------------------------------------------------
/*! \fn Draw Filter : This will be used to filter This object for draing, used to limit the amount drawn onto the screen at a given time.
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
/*! \fn Draw Filter (Overload) : This will be used to filter This object for draing, used to limit the amount drawn onto the screen at a given time.
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

	m_SelectedCircle.setPosition(m_GameObjectPos - m_ColonistBody.getSize()); 
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
/*! \fn Get Current Layer : This will return the value for the current layer which the colonist is on.
*
*/
int Colonist::m_GetCurrentLayer()
{
	return m_iCurrentLayer;
}

Cells * Colonist::m_GetCurrentCell()
{
	return m_CurrentCell;
}

//--------------------------------------------------------
/*! \fn Get Current Job : Will be used to get the value of the current job the colonist is performing.
*
*/
job Colonist::m_GetCurrentJob()
{
	return m_CurrentJob;
}

void Colonist::m_SetNeededWood(float woodNeeded)
{
	m_iNeededWood = woodNeeded; 
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

				m_ResetPathfinding();
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

		if (endCell != nullptr)
		{
			m_EndCell = endCell;
		}
		else
		{
			// Check if the current end cell exists. 
			throw 42; 
		}

		if (m_EndCell == m_CurrentCell)
		{
			// Check if the colonist has reached their destination. 

			return 0; 
		}

		if ((m_EndCell != nullptr) && (m_CurrentCell != nullptr))
		{
			// std::cout << "Findng New Path" << std::endl;

			m_ResetPathfinding();

			if (m_CurrentCell->m_GetLayer() == m_EndCell->m_GetLayer())
			{

				do
				{

					Pathfinding l_clPathfinding;

					l_clPathfinding.m_InitAlgorithm(m_CurrentCell, m_EndCell);

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
		bool l_bPrintError = true; 

		m_ResetPathfinding(); 

		switch(i)
		{
		case 3:
			// This will timeout the function.
			
			if (l_bPrintError == true)
			{
				std::cout << "Unable to Perform Function : Error Code : " << i << std::endl;
			}
			
			return 1;
			break;

		case 42:
			// If the function attempts to access a nullptr it will exit. 
			
			if (l_bPrintError == true)
			{
				std::cout << "Unable to Perform Function : Error Code : " << i << std::endl;
			}

			return 1;
			break;

		default:
			
			if (l_bPrintError == true)
			{
				std::cout << "Unable to Perform Function : Error Code : " << i << std::endl;
			}

			return 1; 
			break;
		}
	}

	return 0; 
}

void Colonist::m_AssignTree(WoodResource * newTarget)
{
	m_TargetTree = newTarget; 
}

bool Colonist::m_AtTargetTree()
{
	if (m_TargetTree == nullptr)
	{
		return false; 
	}

	else if (m_TargetTree->m_GetCurrentCell()->m_CheckCellBounds(m_GetObjectPos().x, m_GetObjectPos().y))
	{

		return true;
	}

	return false;
}

void Colonist::m_AssignBuild(BuildingObject * newTarget)
{
	m_TargetBuild = newTarget; 
}

bool Colonist::m_AtTargetBuild()
{
	if (m_TargetBuild == nullptr)
	{
		return false;
	}
	else if (m_TargetBuild->m_CheckBuildingBounds(m_GetObjectPos().x, m_GetObjectPos().y))
	{

		return true;
	}

	return false;
}

void Colonist::m_ResetPathfinding()
{
	m_iCurrentMoveTo = 0;

	m_Path.clear();

	m_PathLine.clear();

	m_bFindNewPath = true;
}

void Colonist::m_SetInteractableObject(BuildingObject * newTarget)
{
	m_InteractableObject = newTarget;
}

bool Colonist::m_bAtInteratableObject()
{
	if (m_InteractableObject == nullptr)
	{
		return false;
	}
	else if (m_InteractableObject->m_CheckBuildingBounds(m_GetObjectPos().x, m_GetObjectPos().y))
	{

		return true;
	}

	return false;
}

//--------------------------------------------------------
/*! \fn Get Find New Path : This will determine if a new path should be generated for the colonist.
*
*/
bool Colonist::m_GetFindNewPath()
{
	return m_bFindNewPath;
}

//--------------------------------------------------------
/*! \fn Create Path Line : This will create a line from the colonist's current position to the end point.
*Param One : int - The current position in the movement vector for the colonist.
*/
void Colonist::m_CreatePathLine(int currentPos)
{
	m_PathLine.clear(); 

	m_PathLine.setPrimitiveType(sf::LineStrip); 

	for (unsigned int i = currentPos; i < m_Path.size(); i++)
	{
		m_PathLine.append(m_Path[i]->m_GetCellCentre()); 
	}
}

void Colonist::m_SelectColonist(bool selected)
{
	if (selected)
	{
		m_bSelected = true; 

		m_clInfoWindow.m_SetDisplay(true);
	}
	else
	{
		m_bSelected = false;

		m_clInfoWindow.m_SetDisplay(false); 
	}
}

bool Colonist::m_GetSelectedValue()
{
	return m_bSelected;
}
