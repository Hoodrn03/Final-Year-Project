/*! \file This will be the basis for a building object within the game. */

#pragma once

#include "defs.h"

#include "GameObject.h"

class BuildingObject : public GameObject
{
public:

	BuildingObject();

	~BuildingObject();

private:

	// Data Members 

	sf::RectangleShape m_BuildingBody; 

	std::string m_sBuildingType; 

public:

	// Member Functions 

	void m_SetupBuildingObject(sf::Vector2f dimentions, sf::Vector2f position);

	void m_SetupBuildingObject(sf::Vector2f dimentions, sf::Vector2f position, std::string buildingType);

	void m_Update() override;

	void m_DrawGameObject(sf::RenderWindow & window) override;

	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight) override;

	void m_SetObjectPos(float x, float y) override;

	bool m_CheckBuildingBounds(float x, float y); 

};
