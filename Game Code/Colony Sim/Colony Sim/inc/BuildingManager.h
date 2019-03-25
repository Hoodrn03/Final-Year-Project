/*! \file This will handle all of the bulding objects within the game. */

#pragma once

#include "defs.h"

#include "BuildingObject.h"

/*! \class This will control the creation and maintenance of building objects within the game. */
class BuildingManager
{
public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	BuildingManager();

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~BuildingManager();

private:

	// Data Members 

	/*! \var A list of building objects both build and unbuilt. */
	std::vector<BuildingObject> v_Buildings; 

	/*! \var The local stoage for the font used by the buttons. */
	sf::Font m_LocalFont;

	/*! \var A list of buttons associated with building objects. */
	std::vector<tgui::Button::Ptr> v_BuildingButtons; 

	/*! \var This boolean will be used to check if a building object should be created. */
	bool m_bBuildObject = false; 

	/*! \var The current item to be build (will be passed ito the building object). */
	std::string m_sCurrentObjectToBuild = "Null"; 

	/*! \var The ghost outline for the possible building object, used to aid with placement of buildings. */
	sf::RectangleShape m_PlaceholderBuilding; 

	/*! \var The local definition of the width and height for the new buildings. */
	float m_fBuildingWidth, m_fBuildingHeight; 

	// Local Textures

	/*! \var The local texture for the Wood Wall. */
	sf::Texture * m_WoodWall; 

	/*! \var The local texture for the Wood Door. */
	sf::Texture * m_WoodDoor; 

	sf::Texture * m_Bed; 

public:

	/*! \var The ever present button used to create the other buttons. */
	tgui::Button::Ptr m_BuildingActionButton;

	/*! \var Used to display the buttons. */
	bool m_bDisplayButtons = false;

	/*! \var Used to check if the buttons have been created, (prevents multiple copies). */
	bool m_bButtonsCreated = false;

	/*! \var Used to remove the buttons and reset other booleans. */
	bool m_bButtonsRemoved = false;

public:

	// Member Functions 

	//--------------------------------------------------------\\
	//						Setup 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Setup : Used to initalize the variables for this class. 
	*
	*/
	void m_Setup(); 

	//--------------------------------------------------------
	/*! \fn Setup : Used to initalize the variables for this class.
	*Param One : Vector2f - The size of the cells, (used to set the height and width for the buildings).  
	*/
	void m_Setup(sf::Vector2f cellSize);

	//--------------------------------------------------------\\
	//				Colouring and Textureing
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn AssignTextures : Used to store textures locally to easily assign them. 
	*Param One : map<String, Texture> - The current texture map containing all currently loaded textures. 
	*/
	void m_AssignTextures(std::map<std::string, sf::Texture> &m_TextureMap); 

	//--------------------------------------------------------
	/*! \fn AssignFont : Used to store a font locally for use with the buttons. 
	*Param One : Font - The new font to be used by this class. 
	*/
	void m_AssignFont(sf::Font mainFont);

	//--------------------------------------------------------\\
	//				Creation of Buildings
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn AddBuilding : Used to add a new building into the game world. 
	*Param One : String - The type of building (Todo make enum). 
	*Param Two : Cells - The cell location for the new building. 
	*/
	void m_AddBuilding(std::string buildingType, Cells * newCell);

	//--------------------------------------------------------
	/*! \fn SetBuildObjects : This will be used to allow the player to build buildings into the game world. 
	*Param One : bool - Either allow for forbid building within the game. 
	*/
	void m_SetBuildObjects(bool buildNewObjects);

	//--------------------------------------------------------
	/*! \fn SetCurrentObjectToBuild : Set the type of object to build within the game.
	*Param One : String - The name of the object to build. 
	*/
	void m_SetCurrentObjectToBuild(std::string buildingType);

	//--------------------------------------------------------\\
	//						Update 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Update : Used to update the building stored within this class; (Possibly split into more functions). 
	*Param One : Vector2f - The mouse's current position. 
	*Param Two : bool - The current state of the LMB (left mouse button). 
	*Param Three : Cells - The current current cell the mouse is inside. 
	*Param Four : Vector2f - The upper bounds for the current view. 
	*Param Five : Vector2f - The lower bounds for the current view. 
	*/
	void m_Update(sf::Vector2f mousePos, bool mouseDown, Cells * currentCell, sf::Vector2f upperBounds, sf::Vector2f lowerBounds);

	//--------------------------------------------------------\\
	//				Drawing and Rendering
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn DrawBuildings : This will be used to draw all of the buildings into the game world. 
	*Parm One : RenderWindow - The main game window for the game. 
	*/
	void m_DrawBuildings(sf::RenderWindow &window); 

	//--------------------------------------------------------
	/*! \fn DrawFilter : This is used to limit the drawing of the buildings within the game. 
	*
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, int currentLayer);

	//--------------------------------------------------------\\
	//					Positioning
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn GetClosestBuilding : Used to get a building which is closest to a specific object in game space.
	*Param One : Vector2f - The position of the other object for comparason. 
	*/
	BuildingObject * m_GetClosestBuilding(sf::Vector2f objectPos); 

	BuildingObject * m_FindObjectWithName(std::string objectName); 

	//--------------------------------------------------------\\
	//						Buttons 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn CreateBuildingButtons : Used to initalize the building buttons at the start of the game. 
	*Param One : float - The width for the current game window.
	*Param Two : float - The height for the current game window. 
	*/
	void m_CreateBuildingButtons(float windowWidth, float windowHeight);

	//--------------------------------------------------------
	/*! \fn DrawBuildingButtons : Used to drawthe buttons into the game.
	*
	*/
	void m_DrawBuildingButtons();

	//--------------------------------------------------------
	/*! \fn GetBuildingButtons : Used to get access to the vector of buttons. 
	*
	*/
	std::vector<tgui::Button::Ptr> m_GetBuildingButtons();

	 

	

};