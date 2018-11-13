#pragma once

#include "defs.h"

#include "GameObject.h"

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

	// Member Functions 

public:

	void m_CreateColonistBody(sf::Vector2f dimentions, sf::Vector2f position); 

	void m_Update() override; 

	void m_DrawGameObject(sf::RenderWindow & window) override;

	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight) override;

	void m_SetObjectPos(float x, float y) override;

};