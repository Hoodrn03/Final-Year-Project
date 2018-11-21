/*! \file Colonist.h
*
* This class holds all of the functionality for the colonists, it will allow for them to move freely 
* around the game map, as well as allowing for them to manipulate the game world under the player's commands. 
*
*/

#pragma once

#include "defs.h"

#include "GameObject.h"
#include "Pathfinding.h"
#include "Cells.h"

/*! \class This class will hold the functionality for a single colonist within the game. */
class Colonist : public GameObject
{

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Colonist();

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor 
	*
	*/
	~Colonist();

	// Data Members 

private:

	/*! \var This will be the colonist's main body within the game. */
	sf::RectangleShape m_ColonistBody; 

	/*! \var This class will handle the main functionality of finding paths between cells. */
// 	Pathfinding m_clPathfinding; 

	/*! \var Will be used to genearte a new path for the colonist,if they have reached the end of their current one. */
	bool m_bFindNewPath = true; 

	/*! \var This will be the current cell on the grid the colonist is currently inside. */
	Cells * m_CurrentCell = nullptr; 

	unsigned int pos = 0; 

	sf::Clock m_MovementClock; 

	const float m_fmovementTimer = 0.5f; 

	std::deque<Cells*> m_Path; 

	std::vector<tileSet> m_Obstructions = { _ROCK }; 

	// Member Functions 

public:

	//--------------------------------------------------------
	/*! \fn Create Colonist Body : This will be used to initalize the rectangle shape dor what will become the colonist. 
	*Param One : Vector2f - This will be the dimentions for the colonist. 
	*Param Two : Vector2f - This Will be the position in world space for the colonist. 
	*/
	void m_CreateColonistBody(sf::Vector2f dimentions, sf::Vector2f position); 

	//--------------------------------------------------------
	/*! \fn Create Colonist Body (Overload) : This will be used to initalize the rectangle shape dor what will become the colonist. 
	*Param One : Vector2f - This will be the dimentions for the colonist.
	*Param Two : Cells - The cell the colonist will start in. 
	*/
	void m_CreateColonistBody(sf::Vector2f dimentions, Cells * currentCell);

	void m_UpdateCurrentCell(Cells * newCurrentCell);

	//--------------------------------------------------------
	/*! \fn Update : This will be used to update the logic for this class. 
	*
	*/
	void m_Update() override; 

	//--------------------------------------------------------
	/*! \fn Draw Game Object : This will be used to render the colonist. 
	*Param One : RenderWindow - The current game widow for the object to be drawn onto. 
	*/
	void m_DrawGameObject(sf::RenderWindow & window) override;

	//--------------------------------------------------------
	/*! \fn Draw Filter : This will be used to filter this object for draing, used to limit the amount drawn onto the screen at a given time. 
	*Param One : Vector2f - The top left corner of the game view. 
	*Param Two : Vector2f - The bottom right corner of the game view. 
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight) override;

	//--------------------------------------------------------
	/*! \fn Set Object Pos : This will be used to update the current position of the game object. 
	*Param One : float - The new X for the object. 
	*Param Two : float - The new Y for the object.
	*/
	void m_SetObjectPos(float x, float y) override;

	//--------------------------------------------------------
	/*! \fn Follow Path : This will be used to move the colonist along the new found path. 
	*
	*/
	void m_FollowPath(); 

	void m_CalculateMovementVector(); 

	//--------------------------------------------------------
	/*! \fn Find New Path : This will initalize a new path for the colonist. 
	*Param One : Cells - This will be the new end cell for the colonist. 
	*/
	int m_FindNewPath(Cells * endCell); 

	//--------------------------------------------------------
	/*! \fn Get Find New Path : This will determine if a new path should be generated for the colonist. 
	*
	*/
	bool m_GetFindNewPath(); 
};