#include "BuildingObject.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
BuildingObject::BuildingObject()
{
}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
BuildingObject::~BuildingObject()
{
}

void BuildingObject::m_SetupBuildingObject(sf::Vector2f dimentions, sf::Vector2f position, std::string buildingType, Cells * newCell, float woodRequired)
{
	// Todo : if the newCell is a nullptr then exit with an error (possibly use a try catch). 

	m_BuildingBody.setSize(dimentions);
	m_BuildingBody.setOrigin(m_BuildingBody.getGlobalBounds().width * 0.5f, m_BuildingBody.getGlobalBounds().height * 0.5f);

	m_BuildingBody.setFillColor(sf::Color(255, 255, 255, 100));

	m_SetObjectPos(position.x, position.y);

	m_sBuildingType = buildingType;

	if (newCell == nullptr)
	{
		std::cout << "Invalid cell" << std::endl;
	}

	m_CurrentCell = newCell;

	m_CurrentLayer = newCell->m_GetLayer(); 
	
	m_fWoodRequired = woodRequired; 
	
	// std::cout << "Wood needed for this  :  " << m_fWoodRequired; 
}

//--------------------------------------------------------
/*! \fn AssignTexture : Used to assign the new building a texture.
*Param One : The new texture for the building.
*/
void BuildingObject::m_AssignTexture(sf::Texture * newTexture)
{
	m_localTexture = newTexture;

	m_BuildingBody.setTexture(m_localTexture);
}

//--------------------------------------------------------
/*! \fn Update : This will be used to update the current state of this building.
*
*/
void BuildingObject::m_Update()
{
	if (m_bFinishedBuilding == true)
	{
		if (m_bFirstBuild == true)
		{
			m_bFirstBuild = false;

			if (m_sBuildingType == "Wall")
			{
				m_CurrentCell->m_bObstruction = true;
			}

			m_BuildingBody.setFillColor(sf::Color(255, 255, 255, 255));
		}
	}
}

//--------------------------------------------------------
/*! \fn DrawGameObject : USed to draw this object into the game world.
*Param One : RenderWindow - The current game window for the game.
*/
void BuildingObject::m_DrawGameObject(sf::RenderWindow & window)
{
	if (m_DrawItem == _DRAW)
	{
		window.draw(m_BuildingBody);
	}
}

//--------------------------------------------------------
/*! \fn DrawFilter : Used to limit the drawing of this game object.
*Param One : Vector2f - The top left of the game view.
*Param Two : Vector2f - The bottom right of the game view.
*/
void BuildingObject::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{

	if (((m_BuildingBody.getPosition().x > topLeft.x) && (m_BuildingBody.getPosition().y > topLeft.y))
		&& ((m_BuildingBody.getPosition().x < bottomRight.x) && (m_BuildingBody.getPosition().y < bottomRight.y)))
	{
		m_DrawItem = _DRAW;
	}
	else
	{
		m_DrawItem = _NO_DRAW;
	}
}

void BuildingObject::m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, int currentLayer)
{
	if (m_CurrentLayer == currentLayer)
	{
		if (((m_BuildingBody.getPosition().x > topLeft.x) && (m_BuildingBody.getPosition().y > topLeft.y))
			&& ((m_BuildingBody.getPosition().x < bottomRight.x) && (m_BuildingBody.getPosition().y < bottomRight.y)))
		{
			m_DrawItem = _DRAW;
		}
		else
		{
			m_DrawItem = _NO_DRAW;
		}
	}
	else
	{
		m_DrawItem = _NO_DRAW;
	}

}

//--------------------------------------------------------
/*! \fn SetObjectPos : Used to change the position of this game object.
*Param One : float - The new X coord.
*Param Two : float - The new Y coord.
*/
void BuildingObject::m_SetObjectPos(float x, float y)
{
	m_BuildingBody.setPosition(x, y); 

	m_GameObjectPos = sf::Vector2f(x, y); 
}

//--------------------------------------------------------
/*! \fn GetCurrentCell : Used to access the cell location for the building.
*
*/
Cells * BuildingObject::m_GetCurrentCell()
{
	return m_CurrentCell;
}

//--------------------------------------------------------
/*! \fn CheckBuildingBounds : Checks if a point is inside this building object.
*Param One : float - The X position to check.
*Param Two : float - The Y position to check.
*/
bool BuildingObject::m_CheckBuildingBounds(float x, float y)
{
	if (this != nullptr)
	{
		if (m_BuildingBody.getGlobalBounds().contains(x, y))
		{
			return true;
		}
	}

	return false; 
}

	//--------------------------------------------------------
	/*! \fn WorkBuilding : Allows a colonist to interact with this object and 'Build it'. 
	*Param One : The work speed of the colonist working on this building. 
	*/
void BuildingObject::m_WorkBuilding(float workSpeed)
{
	if (m_fCurrentWood >= m_fWoodRequired)
	{

		if (m_bFinishedBuilding == false)
		{
			m_fCurrentConstruction -= workSpeed;

			// std::cout << "Working ... "; 
		}

		if (m_fCurrentConstruction <= 0)
		{
			// std::cout << "/nFinished" << std::endl;

			m_bFinishedBuilding = true;

			// Todo : Change the string into an enum to make it easier to change and manage. 
		}

	}
}

void BuildingObject::m_AddWoodToBuilding(float woodToAdd)
{
	m_fCurrentWood += woodToAdd; 
}

float BuildingObject::m_GetWoodNeeded()
{
	return m_fWoodRequired;
}

bool BuildingObject::m_NeedWood()
{
	if (m_fCurrentWood >= m_fWoodRequired)
	{
		return false; 
	}

	std::cout << std::boolalpha << "Need Wood ? ";

	return true;
}

std::string BuildingObject::m_GetBuildingType()
{
	return m_sBuildingType;
}
