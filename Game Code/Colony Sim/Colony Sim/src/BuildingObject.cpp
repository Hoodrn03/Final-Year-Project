#include "BuildingObject.h"

BuildingObject::BuildingObject()
{
}

BuildingObject::~BuildingObject()
{
}

void BuildingObject::m_SetupBuildingObject(sf::Vector2f dimentions, sf::Vector2f position, std::string buildingType, Cells * newCell)
{
	// Todo : if the newCell is a nullptr then exit with an error (possibly use a try catch). 

	m_BuildingBody.setSize(dimentions);
	m_BuildingBody.setOrigin(m_BuildingBody.getGlobalBounds().width * 0.5f, m_BuildingBody.getGlobalBounds().height * 0.5f); 

	m_SetObjectPos(position.x, position.y);

	m_sBuildingType = buildingType;

	if (newCell == nullptr)
	{
		std::cout << "Invalid cell" << std::endl;
	}

	m_CurrentCell = newCell; 
}

void BuildingObject::m_AssignTexture(sf::Texture newTexture)
{
	m_localTexture = newTexture;

	m_BuildingBody.setTexture(&m_localTexture);
}

void BuildingObject::m_Update()
{
	if (m_bFinishedBuilding == true)
	{
		if (m_bFirstBuild == true)
		{
			m_bFirstBuild = false;

			m_CurrentCell->m_bObstruction = true; 
		}

		m_BuildingBody.setTexture(&m_localTexture);
	}
}

void BuildingObject::m_DrawGameObject(sf::RenderWindow & window)
{
	window.draw(m_BuildingBody); 
}

void BuildingObject::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
}

void BuildingObject::m_SetObjectPos(float x, float y)
{
	m_BuildingBody.setPosition(x, y); 

	m_GameObjectPos = sf::Vector2f(x, y); 
}

Cells * BuildingObject::m_GetCurrentCell()
{
	return m_CurrentCell;
}

bool BuildingObject::m_CheckBuildingBounds(float x, float y)
{
	if (m_BuildingBody.getGlobalBounds().contains(x, y))
	{
		return true;
	}

	return false; 
}

void BuildingObject::m_WorkBuilding(float workSpeed)
{
	if (m_bFinishedBuilding == false)
	{
		m_fCurrentConstruction -= workSpeed;

		std::cout << "Working ... "; 
	}
	
	if (m_fCurrentConstruction <= 0)
	{
		std::cout << "/nFinished" << std::endl;

		m_bFinishedBuilding = true; 

		// Todo : Change the sting into an enum to make it easier to change and manage. 
	}


}
