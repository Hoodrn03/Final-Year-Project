/*! \file This will be the basis for a building object within the game. */

#pragma once

#include "defs.h"

#include "GameObject.h"
#include "Cells.h"

/*! \class This is a single building object within the game. */
class BuildingObject : public GameObject
{
public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	BuildingObject();

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~BuildingObject();

private:

	// Data Members 

	/*! \var The main body for the building, it will have a size, pos and a texture. */
	sf::RectangleShape m_BuildingBody; 

	/*! \var The current building type this object has (either wall or door atm)*/
	std::string m_sBuildingType; 

	/*! \var The woork required to build this object (todo add varying build times for different objects). */
	const float m_fWorkRequired = 150.f;

	/*! \var The current construction level of this object (once 0 object is built). */
	float m_fCurrentConstruction = m_fWorkRequired;

	float m_fWoodRequired = 0; 

	float m_fCurrentWood = 0; 

	/*! \var Used to check when the building is first built. */
	bool m_bFirstBuild = true; 

	/*! \var The cell location for the building. */
	Cells * m_CurrentCell = nullptr; 

	/*! \var The local texture for this object. */
	sf::Texture m_localTexture; 

public:

	/*! \var Used to determine if the building is finished. */
	bool m_bFinishedBuilding = false;

	// Member Functions 

	//--------------------------------------------------------\\
	//						Setup 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn SetupBuildingObject : Used to create a building object for the game. 
	*Param One : Vector2f - The dimentions for the building. 
	*Param Two : Vector2f - The position for the building. 
	*Param Three : String - The type of building to create.
	*Param Four : Cells - The cell location for the building.
	*/
	void m_SetupBuildingObject(sf::Vector2f dimentions, sf::Vector2f position, std::string buildingType, Cells * newCell);

	void m_SetupBuildingObject(sf::Vector2f dimentions, sf::Vector2f position, std::string buildingType, Cells * newCell, float woodRequired);

	//--------------------------------------------------------\\
	//				Colouring and Texturing
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn AssignTexture : Used to assign the new building a texture. 
	*Param One : The new texture for the building. 
	*/
	void m_AssignTexture(sf::Texture newTexture); 

	//--------------------------------------------------------\\
	//						Update 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Update : This will be used to update the current state of this building. 
	*
	*/
	void m_Update() override;

	//--------------------------------------------------------\\
	//				Rendering and Drawing 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn DrawGameObject : USed to draw this object into the game world. 
	*Param One : RenderWindow - The current game window for the game. 
	*/
	void m_DrawGameObject(sf::RenderWindow & window) override;

	//--------------------------------------------------------
	/*! \fn DrawFilter : Used to limit the drawing of this game object. 
	*Param One : Vector2f - The top left of the game view.
	*Param Two : Vector2f - The bottom right of the game view. 
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight) override;

	//--------------------------------------------------------\\
	//						Positioning
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn SetObjectPos : Used to change the position of this game object. 
	*Param One : float - The new X coord.
	*Param Two : float - The new Y coord. 
	*/
	void m_SetObjectPos(float x, float y) override;

	//--------------------------------------------------------
	/*! \fn GetCurrentCell : Used to access the cell location for the building.
	*
	*/
	Cells * m_GetCurrentCell(); 

	//--------------------------------------------------------
	/*! \fn CheckBuildingBounds : Checks if a point is inside this building object. 
	*Param One : float - The X position to check.
	*Param Two : float - The Y position to check.
	*/
	bool m_CheckBuildingBounds(float x, float y); 

	//--------------------------------------------------------\\
	//					Colonist Interaction
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn WorkBuilding : Allows a colonist to interact with this object and 'Build it'. 
	*Param One : The work speed of the colonist working on this building. 
	*/
	void m_WorkBuilding(float workSpeed);

	void m_AddWoodToBuilding(float woodToAdd); 

	float m_GetWoodNeeded(); 

	bool m_NeedWood(); 

};
