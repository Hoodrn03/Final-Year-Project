#pragma once

#include "defs.h"

#include "GameObject.h"
#include "Pathfinding.h"
#include "Cells.h"

/*! \class This class will hold the functionality for a single colonist within the game. */
class Colonist : public GameObject
{

public:

	Colonist();

public:

	~Colonist();

	// Data Members 

private:

	sf::RectangleShape m_ColonistBody; 

	Pathfinding m_clPathfinding; 

	bool m_bFindNewPath = true; 

	Cells * m_CurrentCell; 

	// Member Functions 

public:

	void m_CreateColonistBody(sf::Vector2f dimentions, sf::Vector2f position); 

	void m_CreateColonistBody(sf::Vector2f dimentions, Cells * currentCell);

	void m_Update() override; 

	void m_DrawGameObject(sf::RenderWindow & window) override;

	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight) override;

	void m_SetObjectPos(float x, float y) override;

	void m_FollowPath(); 

	void m_FindNewPath(Cells * endCell); 

	bool m_GetFindNewPath(); 
};