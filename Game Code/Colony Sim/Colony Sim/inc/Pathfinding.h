/*! \file Pathfinding.h
*
* This will use the pathfinding algorith A* to find a path from one cell to another cell. 
* It will output a path of cells. 
*
*/

#pragma once

#include "defs.h"

#include "Cells.h"

/*! \class This will use A* to find the shortest path between two cells. */
class Pathfinding
{

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Pathfinding(); 

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~Pathfinding();

	// Data Members 

private:

	/*! \var This will check if the end point had been found and will trigger the path to be traced. */
	bool m_bPathFound = true; 

	/*! \var The closed set, contains cells already evaluated.  */
	std::vector<Cells*> m_ClosedSet;

	/*! \var The open set, contains cells yet to be evaluated. */
	std::vector<Cells*> m_OpenSet;

	/*! \var The current cell being evaluated. */
	Cells * m_CurrentCell = nullptr;

	/*! \var The start cell for the algorithm */
	Cells * m_StartCell = nullptr; 

	/*! \var The end cell for the algorithm */
	Cells * m_EndCell = nullptr; 

	/*! \var The final path the algorithm will output. */
	std::deque<Cells*> m_FinalPath; 

	// Member Functions

public:

	//--------------------------------------------------------
	/*! \fn InitAlgorithm : This will begin the algorithm. 
	*Param One : Cells - The start cell for the algorithm.
	*Param Two : Cells - The end cell for the algorithm. 
	*/
	void m_InitAlgorithm(Cells * startCell, Cells * endCell); 

	//--------------------------------------------------------
	/*! \fn RunAStarAlgorithm : This will be used to continue the algorithm. 
	*
	*/
	void m_RunAStarAlgorithm();

	//--------------------------------------------------------
	/*! \fn RunAStarAlgorithm : This will be used to continue the algorithm.
	*
	*/
	void m_RunAStarAlgorithm(std::vector<tileSet> obstructions);

	//--------------------------------------------------------
	/*! \fn CalcDist : This will be used to find the literal distance between two cells. 
	*Param One : Cells - The first cell. 
	*Param Two : Cells - The second cell. 
	*/
	sf::Vector2f m_CalcDist(Cells * pointOne, Cells * pointTwo); 

	//--------------------------------------------------------
	/*! \fn CalculateGScore : This will find the gscore. The cost of getting from start node to that node. 
	*Param One : Cells - The start cell for the algorithm. 
	*Param Two : Cells - The current cell for the algorithm. 
	*/
	int m_CalculateGScore(Cells * startCell, Cells * currentCell);

	//--------------------------------------------------------
	/*! \fn CalculateHScore : This will find the hscore. The cost of getting from the current node to the end node. 
	*Param One : Cells - The current cell for the algorithm. 
	*Param Two : Cells - The end cell for the algorithm.
	*/
	int m_CalculateHScore(Cells * currentCell, Cells * endCell); 

	//--------------------------------------------------------
	/*! \fn CalculateFScore : This will find the h score for the current cell. The total sum of the g and h score. 
	*Param One : Cells - The current cell. 
	*/
	int m_CalculateFScore(Cells *currentCell);

	//--------------------------------------------------------
	/*! \fn TracePath : This will be used to find the path by tracing the parents of cells. 
	*
	*/
	void m_TracePath(); 

	//--------------------------------------------------------
	/*! \fn CheckForCompletion : This check to see if the path has been found. 
	*
	*/
	bool m_CheckForCompletion(); 

	//--------------------------------------------------------
	/*! \fn GetCurrentPath : This will be used to access the path outside the class. 
	*
	*/
	std::deque<Cells*> m_GetCurrentPath(); 


};