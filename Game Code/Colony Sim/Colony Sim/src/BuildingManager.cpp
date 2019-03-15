#include "BuildingManager.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
BuildingManager::BuildingManager()
{

}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
BuildingManager::~BuildingManager()
{
}

//--------------------------------------------------------
/*! \fn Setup : Used to initalize the variables for this class.
*
*/
void BuildingManager::m_Setup()
{
	// Create the placeholder (ghost) building variables. 

	m_PlaceholderBuilding.setSize(sf::Vector2f(50, 50));
	m_PlaceholderBuilding.setOrigin(m_PlaceholderBuilding.getGlobalBounds().width * 0.5f, m_PlaceholderBuilding.getGlobalBounds().height * 0.5f); 
	m_PlaceholderBuilding.setFillColor(sf::Color::Transparent);
	m_PlaceholderBuilding.setOutlineColor(sf::Color::White);
	m_PlaceholderBuilding.setOutlineThickness(0.5f);
}

//--------------------------------------------------------
/*! \fn Setup : Used to initalize the variables for this class.
*Param One : Vector2f - The size of the cells, (used to set the height and width for the buildings).
*/
void BuildingManager::m_Setup(sf::Vector2f cellSize)
{
	// Use the current cell size to create the correct sized building. 

	m_fBuildingWidth = cellSize.x;
	m_fBuildingHeight = cellSize.y; 

	// Create the placeholder (ghost) building variables.

	m_PlaceholderBuilding.setSize(sf::Vector2f(m_fBuildingWidth, m_fBuildingHeight));
	m_PlaceholderBuilding.setOrigin(m_PlaceholderBuilding.getGlobalBounds().width * 0.5f, m_PlaceholderBuilding.getGlobalBounds().height * 0.5f);
	m_PlaceholderBuilding.setFillColor(sf::Color::Transparent);
	m_PlaceholderBuilding.setOutlineColor(sf::Color::White);
	m_PlaceholderBuilding.setOutlineThickness(0.5f);
}

//--------------------------------------------------------
/*! \fn AssignTextures : Used to store textures locally to easily assign them.
*Param One : map<String, Texture> - The current texture map containing all currently loaded textures.
*/
void BuildingManager::m_AssignTextures(std::map<std::string, sf::Texture> &m_TextureMap)
{
	// Todo : possibly add more varieties of walls and doors to vary the look of builidngs. 

	m_WoodWall = m_TextureMap["woodWallOne"];

	m_WoodDoor = m_TextureMap["woodDoorOne"];
}

//--------------------------------------------------------
/*! \fn AddBuilding : Used to add a new building into the game world.
*Param One : String - The type of building (Todo make enum).
*Param Two : Cells - The cell location for the new building.
*/
void BuildingManager::m_AddBuilding(std::string buildingType, Cells *newCell)
{
	// Create a temp object limited to this function. 
	BuildingObject l_TempBuilding; 

	// Init it's variables. 
	l_TempBuilding.m_SetupBuildingObject(sf::Vector2f(m_fBuildingWidth, m_fBuildingHeight), m_PlaceholderBuilding.getPosition(), buildingType, newCell);

	// Assign a texture. 
	if (buildingType == "Door")
	{
		l_TempBuilding.m_AssignTexture(m_WoodDoor);
	}
	else
	{
		l_TempBuilding.m_AssignTexture(m_WoodWall);
	}

	// Add it to the list of buildings. 
	v_Buildings.push_back(l_TempBuilding); 

}

//--------------------------------------------------------
/*! \fn AssignFont : Used to store a font locally for use with the buttons.
*Param One : Font - The new font to be used by this class.
*/
void BuildingManager::m_AssignFont(sf::Font mainFont)
{
	m_LocalFont = mainFont; 
}

//--------------------------------------------------------
/*! \fn Update : Used to update the building stored within this class; (Possibly split into more functions).
*Param One : Vector2f - The mouse's current position.
*Param Two : bool - The current state of the LMB (left mouse button).
*Param Three : Cells - The current current cell the mouse is inside.
*Param Four : Vector2f - The upper bounds for the current view.
*Param Five : Vector2f - The lower bounds for the current view.
*/
void BuildingManager::m_Update(sf::Vector2f mousePos, bool mouseDown, Cells * currentCell, sf::Vector2f upperBounds, sf::Vector2f lowerBounds)
{
	if (v_Buildings.size() > 0)
	{
		for (unsigned int i = 0; i < v_Buildings.size(); i++)
		{
			v_Buildings[i].m_Update(); /*!< Loop through the list of building and update. */
		}
	}

	// Check if a new building should be created. 
	if (m_bBuildObject == true)
	{
		m_PlaceholderBuilding.setPosition(mousePos);

		if (mouseDown == true)
		{
			bool l_bAlreadyThere = false; 

			if (mousePos.y <= upperBounds.y + 75) 
			{
				l_bAlreadyThere = true; 
			}

			if (mousePos.y >= lowerBounds.y - 75)
			{
				l_bAlreadyThere = true;
			}

			if ((currentCell->m_GetTile() == _ROCK) || (currentCell->m_GetTile() == _WATER))
			{
				l_bAlreadyThere = true;
			}

			if (v_Buildings.size() > 0)
			{
				for (unsigned int i = 0; i < v_Buildings.size(); i++)
				{
					if (v_Buildings[i].m_CheckBuildingBounds(mousePos.x, mousePos.y))
					{
						l_bAlreadyThere = true;

						// std::cout << "Building already there" << std::endl;
					}
				}
			}

			if (l_bAlreadyThere == false)
			{
				// std::cout << "Placing " << m_sCurrentObjectToBuild << std::endl;

				m_AddBuilding(m_sCurrentObjectToBuild, currentCell);
			}
		}
	}
}

//--------------------------------------------------------
/*! \fn DrawBuildings : This will be used to draw all of the buildings into the game world.
*Parm One : RenderWindow - The main game window for the game.
*/
void BuildingManager::m_DrawBuildings(sf::RenderWindow & window)
{
	if (v_Buildings.size() > 0)
	{
		for (unsigned int i = 0; i < v_Buildings.size(); i++)
		{
			v_Buildings[i].m_DrawGameObject(window); 
		}
	}

	if (m_bBuildObject == true)
	{
		window.draw(m_PlaceholderBuilding); 
	}
}

//--------------------------------------------------------
/*! \fn DrawFilter : This is used to limit the drawing of the buildings within the game.
*
*/
void BuildingManager::m_DrawFilter()
{
}

//--------------------------------------------------------
/*! \fn GetClosestBuilding : Used to get a building which is closest to a specific object in game space.
*Param One : Vector2f - The position of the other object for comparason.
*/
BuildingObject * BuildingManager::m_GetClosestBuilding(sf::Vector2f objectPos)
{
	// Var setup

	BuildingObject * l_TempBuild = nullptr;

	bool l_FirstBuilding = true;

	float l_PrevXDist, l_PrevYDist;

	float l_XDist, l_YDist;

	if (v_Buildings.size() > 0)
	{
		for (unsigned int i = 1; i < v_Buildings.size(); i++)
		{
			if (v_Buildings[i].m_GetCurrentCell() == nullptr)
			{
				return nullptr;
			}

			// Ensure this only loops through trees chosen to be cut down. 

			if ((v_Buildings[i].m_bFinishedBuilding == false))
			{
				if (v_Buildings[i].m_GetCurrentCell()->m_bObstruction == false)
				{
					if (l_FirstBuilding == true)
					{
						// Find the first tree in the vector to begin the distance evaluations.

						l_TempBuild = &v_Buildings[i];

						l_FirstBuilding = false;

						// Calculate the initial distance between the chosen object and the first tree. 

						if (v_Buildings[i].m_GetObjectPos().x > objectPos.x)
						{
							l_PrevXDist = v_Buildings[i].m_GetObjectPos().x - objectPos.x;
						}
						else
						{
							l_PrevXDist = objectPos.x - v_Buildings[i].m_GetObjectPos().x;
						}

						if (v_Buildings[i].m_GetObjectPos().y > objectPos.y)
						{
							l_PrevYDist = v_Buildings[i].m_GetObjectPos().y - objectPos.y;
						}
						else
						{
							l_PrevYDist = objectPos.y - v_Buildings[i].m_GetObjectPos().y;
						}
					}

					// Calculate the distance for the next tree. 

					if (v_Buildings[i].m_GetObjectPos().x > objectPos.x)
					{
						l_XDist = v_Buildings[i].m_GetObjectPos().x - objectPos.x;
					}
					else
					{
						l_XDist = objectPos.x - v_Buildings[i].m_GetObjectPos().x;
					}

					if (v_Buildings[i].m_GetObjectPos().y > objectPos.y)
					{
						l_YDist = v_Buildings[i].m_GetObjectPos().y - objectPos.y;
					}
					else
					{
						l_YDist = objectPos.y - v_Buildings[i].m_GetObjectPos().y;
					}

					// See if the new distance is shorter than the preveous one. 

					if ((l_XDist <= l_PrevXDist) && (l_YDist <= l_PrevYDist))
					{
						l_TempBuild = &v_Buildings[i];

						l_PrevXDist = l_XDist;
						l_PrevYDist = l_YDist;
					}
				}
			}
		}
	}

	return l_TempBuild;
}

//--------------------------------------------------------
/*! \fn CreateBuildingButtons : Used to initalize the building buttons at the start of the game.
*Param One : float - The width for the current game window.
*Param Two : float - The height for the current game window.
*/
void BuildingManager::m_CreateBuildingButtons(float windowWidth, float windowHeight)
{
	// Init Button Sizes.

	int l_iButtonWidth = (windowWidth * 0.15f);
	int l_iButtonHeight = (windowHeight * 0.075f);

	// Create Buttons

	m_BuildingActionButton = tgui::Button::create();

	m_BuildingActionButton->setSize(l_iButtonWidth, l_iButtonHeight);
	m_BuildingActionButton->setPosition(0 + l_iButtonWidth, 0);
	m_BuildingActionButton->setInheritedFont(m_LocalFont);
	m_BuildingActionButton->setText("Buildings");
	m_BuildingActionButton->setTextSize(0);
	m_BuildingActionButton->connect("Pressed", [&]() { m_DrawBuildingButtons(); });

	// Init Button Position. 

	int l_iButtonX = 0;
	int l_iButtonY = 0 + l_iButtonHeight;

	// Clear Button Vector 

	v_BuildingButtons.clear();

	// Cancel Action Button. 

	tgui::Button::Ptr l_TempButton = tgui::Button::create();

	l_TempButton->setSize(l_iButtonWidth, l_iButtonHeight);
	l_TempButton->setPosition(l_iButtonX, l_iButtonY);
	l_TempButton->setInheritedFont(m_LocalFont);
	l_TempButton->setText("Wall");
	l_TempButton->setTextSize(0);
	// Use a lambda function to add a small operation to the button when it is pressed. 
	l_TempButton->connect("Pressed", [&]() { 
		m_SetBuildObjects(true);
		m_SetCurrentObjectToBuild("Wall"); 
	});

	v_BuildingButtons.push_back(l_TempButton);

	// Tree Cutting Button. 

	l_TempButton = tgui::Button::create();

	l_TempButton->setSize(l_iButtonWidth, l_iButtonHeight);
	l_TempButton->setPosition(l_iButtonX + l_iButtonWidth, l_iButtonY);
	l_TempButton->setInheritedFont(m_LocalFont);
	l_TempButton->setText("Door");
	l_TempButton->setTextSize(0);
	l_TempButton->connect("Pressed", [&]() { 
		m_SetBuildObjects(true);
		m_SetCurrentObjectToBuild("Door");
	});

	v_BuildingButtons.push_back(l_TempButton);

	// Temp.

	l_TempButton = tgui::Button::create();

	l_TempButton->setSize(l_iButtonWidth, l_iButtonHeight);
	l_TempButton->setPosition(l_iButtonX + (l_iButtonWidth * 2), l_iButtonY);
	l_TempButton->setInheritedFont(m_LocalFont);
	l_TempButton->setText("Placeholder");
	l_TempButton->setTextSize(0);
	l_TempButton->connect("Pressed", [&]() { });

	v_BuildingButtons.push_back(l_TempButton);
}

//--------------------------------------------------------
/*! \fn SetBuildObjects : This will be used to allow the player to build buildings into the game world.
*Param One : bool - Either allow for forbid building within the game.
*/
void BuildingManager::m_SetBuildObjects(bool buildNewObjects)
{
	m_bBuildObject = buildNewObjects; 
}

//--------------------------------------------------------
/*! \fn SetCurrentObjectToBuild : Set the type of object to build within the game.
*Param One : String - The name of the object to build.
*/
void BuildingManager::m_SetCurrentObjectToBuild(std::string buildingType)
{
	m_sCurrentObjectToBuild = buildingType; 
}

//--------------------------------------------------------
/*! \fn DrawBuildingButtons : Used to drawthe buttons into the game.
*
*/
void BuildingManager::m_DrawBuildingButtons()
{
	m_bDisplayButtons = !m_bDisplayButtons;
}

//--------------------------------------------------------
/*! \fn GetBuildingButtons : Used to get access to the vector of buttons.
*
*/
std::vector<tgui::Button::Ptr> BuildingManager::m_GetBuildingButtons()
{
	m_bButtonsCreated = !m_bButtonsCreated;

	return v_BuildingButtons; 
}
