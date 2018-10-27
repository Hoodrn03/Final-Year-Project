#pragma once

#include "defs.h"

#include "GameObject.h"

class Map : public GameObject
{
public: 
	
	Map(); 

public: 

	~Map(); 

	// Data Members 

private: 

	sf::RectangleShape m_MapObject; 

	// Member Functions 

public: 

	void m_SetUpGameMap(sf::Vector2f dimentions, sf::Vector2f position); 

	void m_DrawGameObject(sf::RenderWindow & window) override; 

	void m_SetObjectPos(float x, float y) override; 

};