#include "../inc/Pathfinding.h"

Pathfinding::Pathfinding()
{
}

Pathfinding::~Pathfinding()
{
}

void Pathfinding::m_InitAlgorithm(Cells * startCell, Cells * endCell)
{
	m_StartCell = startCell;

	m_StartCell->m_SetCellColour(255, 255, 255);

	m_EndCell = endCell; 

	m_EndCell->m_SetCellColour(255, 255, 255); 

	m_CurrentCell = startCell; 
}

void Pathfinding::m_RunAStarAlgorithm()
{
	if (m_bPathFound == false)
	{
		if (m_CurrentCell->m_GetCellId() != m_EndCell->m_GetCellId())
		{
			if (std::find(m_ClosedSet.begin(), m_ClosedSet.end(), m_CurrentCell) != m_ClosedSet.end())
			{

			}
			else
			{
				m_ClosedSet.push_back(m_CurrentCell);

				m_CurrentCell->m_SetCellColour(255, 0, 0); 
			}

			for (unsigned int i = 0; i < m_CurrentCell->m_GetNeighbours().size(); i++)
			{
				if (std::find(m_OpenSet.begin(), m_OpenSet.end(), m_CurrentCell->m_GetNeighbours()[i]) != m_OpenSet.end())
				{

				}
				else if(std::find(m_ClosedSet.begin(), m_ClosedSet.end(), m_CurrentCell->m_GetNeighbours()[i]) != m_ClosedSet.end())
				{
					
				}
				else
				{
					m_OpenSet.push_back(m_CurrentCell->m_GetNeighbours()[i]);

					m_CurrentCell->m_GetNeighbours()[i]->m_SetCellColour(0, 255, 0);

					m_CurrentCell->m_GetNeighbours()[i]->m_ParentCell = m_CurrentCell; 
				}
			}

			for (unsigned int i = 0; i < m_OpenSet.size(); i++)
			{
				int l_TempGScore = m_CalculateGScore(m_StartCell, m_OpenSet[i]); 

				if (l_TempGScore <= m_OpenSet[i]->m_iGScore)
				{
					m_OpenSet[i]->m_iGScore = l_TempGScore;
				}

				m_OpenSet[i]->m_iHScore = m_CalculateHScore(m_OpenSet[i], m_EndCell);

				m_OpenSet[i]->m_iFScore = m_CalculateFScore(m_OpenSet[i]);
			}

			m_CurrentCell = m_OpenSet[0]; 

			m_OpenSet.erase(std::remove(m_OpenSet.begin(), m_OpenSet.end(), m_CurrentCell), m_OpenSet.end()); 

			for (unsigned int i = 0; i < m_OpenSet.size(); i++)
			{
				if (m_OpenSet[i]->m_iFScore < m_CurrentCell->m_iFScore)
				{
					m_CurrentCell = m_OpenSet[i]; 
				}
			}

		}
		else
		{
			m_bPathFound = true; 

			m_TracePath();
		}
	}
}

sf::Vector2f Pathfinding::m_CalcDist(Cells * pointOne, Cells * pointTwo)
{
	sf::Vector2f l_NumberOfSteps;

	if (pointOne->m_GetGridPos().x > pointTwo->m_GetGridPos().x)
	{
		l_NumberOfSteps.x = pointOne->m_GetGridPos().x - pointTwo->m_GetGridPos().x;
	}
	else
	{
		l_NumberOfSteps.x = pointTwo->m_GetGridPos().x - pointOne->m_GetGridPos().x;
	}

	if (pointOne->m_GetGridPos().y > m_EndCell->m_GetGridPos().y)
	{
		l_NumberOfSteps.y = pointOne->m_GetGridPos().y - pointTwo->m_GetGridPos().y;
	}
	else
	{
		l_NumberOfSteps.y = pointTwo->m_GetGridPos().y - pointOne->m_GetGridPos().y;
	}

	return l_NumberOfSteps;
}

int Pathfinding::m_CalculateGScore(Cells * startCell, Cells * currentCell)
{
	int l_iCalculatedGScore = 0; 

	sf::Vector2f l_NumberOfSteps = m_CalcDist(startCell, currentCell); 

	do
	{
		if (l_NumberOfSteps.x > 1 && l_NumberOfSteps.y > 1)
		{
			l_NumberOfSteps.x--;
			l_NumberOfSteps.y--;

			l_iCalculatedGScore += _DIAGONAL;
		}
		else if (l_NumberOfSteps.x)
		{
			l_NumberOfSteps.x--;

			l_iCalculatedGScore += _ACROSS;
		}
		else if (l_NumberOfSteps.y)
		{
			l_NumberOfSteps.y--;

			l_iCalculatedGScore += _ACROSS;
		}

	} while (l_NumberOfSteps.x > 0 || l_NumberOfSteps.y > 0); 


	return l_iCalculatedGScore;
}

int Pathfinding::m_CalculateHScore(Cells * currentCell, Cells * endCell)
{
	int l_iCalculatedHScore = 0;

	sf::Vector2f l_NumberOfSteps = m_CalcDist(currentCell, m_EndCell);

	do
	{
		if (l_NumberOfSteps.x > 1 && l_NumberOfSteps.y > 1)
		{
			l_NumberOfSteps.x--;
			l_NumberOfSteps.y--;

			l_iCalculatedHScore += _DIAGONAL;
		}
		else if (l_NumberOfSteps.x)
		{
			l_NumberOfSteps.x--;

			l_iCalculatedHScore += _ACROSS;
		}
		else if (l_NumberOfSteps.y)
		{
			l_NumberOfSteps.y--;

			l_iCalculatedHScore += _ACROSS;
		}

	} while (l_NumberOfSteps.x > 0 || l_NumberOfSteps.y > 0);

	return l_iCalculatedHScore;
}

int Pathfinding::m_CalculateFScore(Cells *currentCell)
{
	int l_iCalculatedFScore = 0; 

	l_iCalculatedFScore += currentCell->m_iGScore; 
	l_iCalculatedFScore += currentCell->m_iHScore; 

	return l_iCalculatedFScore;

}

void Pathfinding::m_TracePath()
{
	std::vector<Cells*> l_Path; 

	Cells* l_CurrentPathPoint; 

	l_CurrentPathPoint = m_CurrentCell; 

	do
	{
		l_Path.push_back(l_CurrentPathPoint);

		l_CurrentPathPoint = l_CurrentPathPoint->m_ParentCell;

	} while (l_CurrentPathPoint->m_GetCellId() != m_StartCell->m_GetCellId());

	l_Path.push_back(l_CurrentPathPoint); 

	for (unsigned int i = 0; i < l_Path.size(); i++)
	{
		l_Path[i]->m_SetCellColour(0, 0, 255);
	}

	m_FinalPath = l_Path; 

}

bool Pathfinding::m_CheckForCompletion()
{
	if (m_bPathFound == true)
	{
		return true; 
	}

	return false;
}

std::vector<Cells*> Pathfinding::m_GetCurrentPath()
{
	return m_FinalPath;
}
