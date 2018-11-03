#pragma once

#include "defs.h"

#include "Cells.h"

class Pathfinding
{

public:

	Pathfinding(); 

public:

	~Pathfinding();

	// Data Members 

private:

	bool m_bPathFound = false; 

	std::vector<Cells*> m_ClosedSet;

	std::vector<Cells*> m_OpenSet;

	Cells * m_CurrentCell;

	Cells * m_StartCell; 

	Cells * m_EndCell; 

	// Member Functions

public:

	void m_InitAlgorithm(Cells * startCell, Cells * endCell); 

	void m_RunAStarAlgorithm();

	sf::Vector2f m_CalcDist(Cells * pointOne, Cells * pointTwo); 

	int m_CalculateGScore(Cells * startCell, Cells * currentCell);

	int m_CalculateHScore(Cells * currentCell, Cells * endCell); 

	int m_CalculateFScore(Cells *currentCell);

	void m_TracePath(); 

	bool m_CheckForCompletion(); 


};