/*! \file This will be the basis for a building object within the game. */

#pragma once

#include "defs.h"

#include "GameObject.h"
#include "Cells.h"

class BuildingObject : public GameObject
{
public:

	BuildingObject();

	~BuildingObject();

private:

	// Data Members 

	sf::RectangleShape m_BuildingBody; 

	std::string m_sBuildingType; 

	const float m_fWorkRequired = 150.f;

	float m_fCurrentConstruction = m_fWorkRequired;

	bool m_bFirstBuild = true; 

	Cells * m_CurrentCell = nullptr; 

	sf::Texture m_localTexture; 

public:

	bool m_bFinishedBuilding = false;

	// Member Functions 

	void m_SetupBuildingObject(sf::Vector2f dimentions, sf::Vector2f position, std::string buildingType, Cells * newCell);

	void m_AssignTexture(sf::Texture newTexture); 

	void m_Update() override;

	void m_DrawGameObject(sf::RenderWindow & window) override;

	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight) override;

	void m_SetObjectPos(float x, float y) override;

	Cells * m_GetCurrentCell(); 

	bool m_CheckBuildingBounds(float x, float y); 

	void m_WorkBuilding(float workSpeed);

};
