/*! \file GameLoop.cpp
*
* This will hold all of the definitions for the class GameLoop.
*
*/

#include "../inc/GameLoop.h"

//--------------------------------------------------------
/*! \fn Constructor
*
*/
Gameloop::Gameloop()
{

}

//--------------------------------------------------------
/*! \fn Deconstructor
*
*/
Gameloop::~Gameloop()
{

}


//--------------------------------------------------------
/*! \fn SetUp : This will be used at startup to initalize any data for the game.
*
*/
int Gameloop::m_SetUp()
{

	// Generate a new seed for the program. 

	std::srand((unsigned int)time(0));

	// Setup Game window 

	if (m_clWindow.m_InitWindow(800, 800, "Colony Sim") != 0)
	{
		return 1;
	}

	m_fWindowWidth = (float)m_clWindow.m_GetWindow().getSize().x;
	m_fWindowHeight = (float)m_clWindow.m_GetWindow().getSize().x;

	// Setup window variables. 
	m_clWindow.m_GetWindow().setKeyRepeatEnabled(false);

	m_clWindow.m_GetWindow().setFramerateLimit(60);

	// Load textures into the game. 

	m_LoadTexturesIntoGame(); 

	// Setup Mouse

	m_clMouse.m_AssignToolTipFont(m_clFontManager.m_GetFrontFromMap("arial")); 

	// Init Gui
	m_clUserInterface.m_InitGui(m_clWindow.m_GetWindow());

	m_ResizeAllItems();

	m_MainMenu(); 

	return 0;

}

void Gameloop::m_CreateMainMenuButtons()
{
	// Empty vector of buttons. 

	v_MainMenuButtons.clear();

	// Init Button Sizes. 

	int l_iButtonWidth = (int)(m_fWindowWidth * 0.2f);
	int l_iButtonHeight = (int)(m_fWindowHeight * 0.1f); 

	// Init Button Position. 

	int l_iButtonX = (int)(m_fWindowWidth * 0.5f) - (int)(l_iButtonWidth * 0.5f);
	int l_iButtonY = (int)(m_fWindowHeight * 0.33f);

	// Create Buttons. 

	tgui::Button::Ptr  l_TempButton = tgui::Button::create();

	l_TempButton->setSize(l_iButtonWidth, l_iButtonHeight);
	l_TempButton->setPosition(l_iButtonX, l_iButtonY);
	l_TempButton->setInheritedFont(m_clFontManager.m_GetFrontFromMap("arial"));
	l_TempButton->setTextSize(0);
	l_TempButton->setText("Exit");
	// Use a lambda function to add a small operation to the button when it is pressed. 
	l_TempButton->connect("Pressed", [&]() {m_clWindow.m_GetWindow().close();  });

	v_MainMenuButtons.push_back(l_TempButton); 

	l_TempButton = tgui::Button::create();

	l_TempButton->setSize(l_iButtonWidth, l_iButtonHeight);
	l_TempButton->setPosition(l_iButtonX, (l_iButtonY + (l_iButtonHeight * 1.5f)));
	l_TempButton->setInheritedFont(m_clFontManager.m_GetFrontFromMap("arial"));
	l_TempButton->setTextSize(0);
	l_TempButton->setText("Begin");

	// Use a lambda function to add a small operation to the button when it is pressed. 
	l_TempButton->connect("Pressed", [&]() {m_BeginGame();  });

	v_MainMenuButtons.push_back(l_TempButton);
}


int Gameloop::m_MainMenu()
{
	// m_BeginGame(); /*!< Use to skip to the main game. */

	// Init pregame logic. 

	m_clUserInterface.m_ClearAllWidgets(); 

	// Add buttons into the UI. 

	m_clUserInterface.m_AddWidget(v_MainMenuButtons); 

	// Start Game Loop. 

	while (m_clWindow.m_GetWindow().isOpen())
	{
		// Update additional logic at the beginning of the frame. 

		m_CheckFramerate(false);

		m_UpdateDeltaTime();

		// Handle Events. 
		m_clEventHandler.m_CheckForEvents(m_clWindow.m_GetWindow());

		m_clUserInterface.m_HandleEvents(m_clEventHandler.m_GetEvent());

		if (m_clEventHandler.m_bCheckForResize())
		{
			m_ResizeAllItems(); 
		}

		// Draw items at the end of the frame. 
		m_RenderMainMenu(); 
	}

	return 0; 
}

void Gameloop::m_RenderMainMenu()
{
	// Clear old objects.  
	m_clWindow.m_GetWindow().clear();

	// Todo: Add items to draw.

	// Draw Gui elements. 

	m_clUserInterface.m_DrawGui();

	// Display new objects. 
	m_clWindow.m_GetWindow().display();
}

void Gameloop::m_BeginGame()
{

	// Empty user interface ojects. 

	m_clUserInterface.m_ClearAllWidgets();

	// Cleanup before the game begins. 

	m_clWindow.m_GetWindow().clear();

	// Init game elements. 

	// Create game map. 

	m_clMap.m_AssignTextures(m_clTextureManager.m_GetTextureMap());

	m_clMap.m_SetUpGameMap(sf::Vector2f(800, 800), sf::Vector2f(0, 0));

	// Add colonists. 
	m_clColonistManager.m_AddColonist(1, sf::Vector2f(5, 5), m_clMap.m_GetGrid(), m_clMap.m_GetGroundLevel());
	m_clColonistManager.m_AssignColonistFonts(m_clFontManager.m_GetFrontFromMap("arial"));

	// Add resources. 
	m_clResourceManagement.m_AddTrees(30, 10.f, m_clMap.m_GetGroundLevel(), m_clMap.m_GetGrid());
	m_clResourceManagement.m_AssignFont(m_clFontManager.m_GetFrontFromMap("arial")); 
	m_clResourceManagement.m_AssignTextures(m_clTextureManager.m_GetTextureMap()); 

	// Prepare Buildings

	m_clBuildingManager.m_AssignFont(m_clFontManager.m_GetFrontFromMap("arial"));
	m_clBuildingManager.m_AssignTextures(m_clTextureManager.m_GetTextureMap());

	m_clBuildingManager.m_Setup(sf::Vector2f(m_clMap.m_GetGrid().m_GetCell(0, 0, 0)->m_GetCellWidth(), 
		m_clMap.m_GetGrid().m_GetCell(0, 0, 0)->m_GetCellHeight()));

	// Add Buttons to GUI. 

	m_ResizeAllItems();

	m_clColonistManager.m_CreateColonistActionButtons(m_clFontManager.m_GetFrontFromMap("arial"), m_clWindow.m_GetWindow());

	m_clUserInterface.m_AddWidget(m_clResourceManagement.m_ActionButton); 

	m_clUserInterface.m_AddWidget(m_clBuildingManager.m_BuildingActionButton); 

	// Begin game.  

	// This will create a new thread for the pathfinding within the game. 
	l_First = std::thread(&Gameloop::m_UpdatePathfinding, this);

	// Start Game Loop. 
	m_Update();

}

//--------------------------------------------------------
/*! \fn Update : This will house the game loop and be used to update any logic. 
*
*/
void Gameloop::m_Update()
{
	while (m_clWindow.m_GetWindow().isOpen())
	{
		// Update additional logic at the beginning of the frame. 

		m_CheckFramerate(false); /*!< This will allow for the current framerate to be easily displayed into the debug console. */

		m_UpdateDeltaTime(); /*!< Updates the change in time since last frame; preventing objects jumping unexpectadly. */

		// Update Mouse. 
		m_clMouse.m_SetMousePos(m_clWindow.m_GetWindow());

		m_clMouse.m_CreateSelectionBox();

		m_clMouse.m_UpdateTooltip(m_clMap.m_GetGrid().m_ConvertWorldPosToGridPos(m_clMouse.m_GetMousePos(), m_clMap.m_GetCurrentLevel())->m_GetTileName(),
			m_clWindow.m_GetViewUpperBounds(), m_clWindow.m_GetViewSize());

		// Handle Events. 
		m_clEventHandler.m_CheckForEvents(m_clWindow.m_GetWindow());

		if (!m_clWindow.m_GetWindow().isOpen())
		{
			// Check the state of the game window and join all threads if needed. 

			l_First.join(); 
		}

		if (m_clEventHandler.m_bCheckForResize())
		{
			// Handle the resizing of the game window. 

			m_ResizeAllItems();
		}

		m_clUserInterface.m_HandleEvents(m_clEventHandler.m_GetEvent()); /*!< Passes current event var into the Gui object. */

		// Update the game map. 
		m_clMap.m_CheckForLayerChange(m_clEventHandler.m_CurrentLayerChangeValue());

		m_clMap.m_Update(); 

		// Update the game resources. 
		m_clResourceManagement.m_Update(); 

		m_clResourceManagement.m_SelectResources(m_clMouse.m_GetTopLeftSelectionBox(), m_clMouse.m_GetBottomRightSelectionBox()); 

		// Update colonists. 
		m_clColonistManager.m_Update(m_clMap.m_GetGrid()); 

		m_clColonistManager.m_UpdateInfoWindows(m_clWindow.m_GetViewLowerBounds(), m_clWindow.m_GetViewSize()); 

		m_clColonistManager.m_SelectColonist(m_clMouse.m_GetTopLeftSelectionBox(), m_clMouse.m_GetBottomRightSelectionBox(), sf::Mouse::isButtonPressed(sf::Mouse::Right)); 

		m_clColonistManager.m_CheckForSelected(); 

		// Update Buildings. 
		m_clBuildingManager.m_Update(m_clMap.m_GetGrid().m_ConvertWorldPosToGridPos(m_clMouse.m_GetMousePos(), m_clMap.m_GetCurrentLevel())->m_GetCellCentre(), 
			m_clMouse.m_GetLMBDown(m_clMap.m_GetMapUpperBounds(), m_clMap.m_GetMapLowerBounds()), m_clMap.m_GetGrid().m_ConvertWorldPosToGridPos(m_clMouse.m_GetMousePos(), 
				m_clMap.m_GetCurrentLevel()), m_clWindow.m_GetViewUpperBounds(), m_clWindow.m_GetViewLowerBounds());

		// Update Gui. 
		m_UpdateButtons();

		// Draw Items. 
		m_RenderGame();

		// Update the game window, at the end of the frame.
		m_clWindow.m_CheckForViewMove(m_clEventHandler.m_CheckViewUpValue(), m_clEventHandler.m_CheckViewDownValue(), m_clEventHandler.m_CheckViewLeftValue(), m_clEventHandler.m_CheckViewRightValue());

		m_clWindow.m_CheckForViewScroll(m_clEventHandler.m_GetMouseWheelState());

		// End of frame removal of objects. 

		m_clResourceManagement.m_DeleteTrees();
	} 

}

void Gameloop::m_UpdateButtons()
{
	// Remove all buttons with RMB

	bool l_bMouseButtonPressed = false; 

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		l_bMouseButtonPressed = true; 

		// std::cout << "RMB Pressed" << std::endl;
	}

	// Manage Buttons. 

	// Resource management buttons. 

	// Todo : Look into tgui callbacks

	if(m_clResourceManagement.m_bDisplayButtons == true)
	{ 
		if (m_clResourceManagement.m_bButtonsCreated == true)
		{
			// Add action buttons. 

			m_clUserInterface.m_AddWidget(m_clResourceManagement.m_GetActionButtons());

			m_clResourceManagement.m_bButtonsRemoved = false;
		}
	}
	else
	{
		if (m_clResourceManagement.m_bButtonsRemoved == false)
		{
			// remove action buttons. 

			m_clUserInterface.m_RemoveWidget(m_clResourceManagement.m_GetActionButtons());

			m_clResourceManagement.m_bButtonsRemoved = true;
		}
	}

	// Building management buttons 

	if (m_clBuildingManager.m_bDisplayButtons == true)
	{
		if (m_clBuildingManager.m_bButtonsCreated == true)
		{
			// Add action buttons. 

			m_clUserInterface.m_AddWidget(m_clBuildingManager.m_GetBuildingButtons());

			m_clBuildingManager.m_bButtonsRemoved = false;
		}
	}
	else
	{
		if (m_clBuildingManager.m_bButtonsRemoved == false)
		{
			// remove action buttons. 

			m_clUserInterface.m_RemoveWidget(m_clBuildingManager.m_GetBuildingButtons());

			m_clBuildingManager.m_bButtonsRemoved = true;

			m_clBuildingManager.m_SetBuildObjects(false); 
		}
	}

	// Colonist management buttons. 

	if (m_clColonistManager.m_bColonistSelected == true)
	{
		if (m_clColonistManager.m_bButtonsCreated == false)
		{
			// Add colonist buttons. 

			m_clUserInterface.m_AddWidget(m_clColonistManager.v_ListOfButtons);

			m_clColonistManager.m_bButtonsRemoved = false;

			m_clColonistManager.m_bButtonsCreated = true;
		}
	}
	else
	{
		if (m_clColonistManager.m_bButtonsRemoved == false)
		{
			// Remove colonist buttons 

			m_clUserInterface.m_RemoveWidget(m_clColonistManager.v_ListOfButtons);

			m_clColonistManager.m_bButtonsRemoved = true;

			m_clColonistManager.m_bButtonsCreated = false;
		}
	}

	if (l_bMouseButtonPressed == true)
	{
		// Remove Resource management buttons 
		m_clUserInterface.m_RemoveWidget(m_clResourceManagement.m_GetActionButtons());

		m_clResourceManagement.m_bDisplayButtons = false;

		m_clResourceManagement.m_bButtonsRemoved = true;

		//Remove Building management buttons

		m_clUserInterface.m_RemoveWidget(m_clBuildingManager.m_GetBuildingButtons());

		m_clBuildingManager.m_bDisplayButtons = false;

		m_clBuildingManager.m_bButtonsRemoved = true;

		m_clBuildingManager.m_SetBuildObjects(false);
	}

}

//--------------------------------------------------------
/*! \fn Update Pathfinding : This will be used to update all of the pathfinding elements in the game.
*
*/
void Gameloop::m_UpdatePathfinding()
{
	// This will continue to loop while the game window is open. 

	while(m_clWindow.m_GetWindow().isOpen())
	{
		// This will be used to get a new path for the colonists. 

		m_clColonistManager.m_Pathfinding(m_clMap.m_GetGrid(), m_clResourceManagement, m_clBuildingManager);
	}
}

//--------------------------------------------------------
/*! \fn Draw Filter : This will be used to limit what is drawn to only those within the game view.
*
*/
void Gameloop::m_DrawFilter()
{
	m_clMap.m_DrawFilter(m_clWindow.m_GetViewUpperBounds(), m_clWindow.m_GetViewLowerBounds());

	m_clResourceManagement.m_DrawFilter(m_clWindow.m_GetViewUpperBounds(), m_clWindow.m_GetViewLowerBounds(), m_clMap.m_GetCurrentLevel());

	m_clColonistManager.m_DrawFilter(m_clWindow.m_GetViewUpperBounds(), m_clWindow.m_GetViewLowerBounds(), m_clMap.m_GetCurrentLevel()); 

	m_clBuildingManager.m_DrawFilter(m_clWindow.m_GetViewUpperBounds(), m_clWindow.m_GetViewLowerBounds(), m_clMap.m_GetCurrentLevel());
}

//--------------------------------------------------------
/*! \fn Render : This will be used to draw all of the objects into the window. 
*
*/
void Gameloop::m_RenderGame()
{
	// Check items for drawing. 

	m_DrawFilter(); 

	// Clear old objects.  
	m_clWindow.m_GetWindow().clear();

	// Todo: Add items to draw. 

	// Draw the Map and Grid at the bottom.
	m_clMap.m_DrawGameObject(m_clWindow.m_GetWindow()); 

	// Draw the Resources above the grid. 
	m_clResourceManagement.m_DrawTrees(m_clWindow.m_GetWindow()); 
	m_clResourceManagement.m_DrawWoodPiles(m_clWindow.m_GetWindow());

	// Draw the colonists at the top.
	m_clColonistManager.m_Render(m_clWindow.m_GetWindow()); 

	// Draw Buildings above colonists. 

	m_clBuildingManager.m_DrawBuildings(m_clWindow.m_GetWindow()); 

	// Draw UI above the other game elements. 

	m_clMouse.m_DrawSelectionBox(m_clWindow.m_GetWindow()); 

	m_clMouse.m_DrawToolTip(m_clWindow.m_GetWindow());

	m_clUserInterface.m_DrawGui(); 

	// Display new objects. 
	m_clWindow.m_GetWindow().display(); 
}

void Gameloop::m_LoadTexturesIntoGame()
{
	m_clTextureManager.m_AddTextureToMap("assets/textures/Grass/hyptosis_grass01.png", "grassOne", m_clWindow.m_GetWindow());
	m_clTextureManager.m_AddTextureToMap("assets/textures/Grass/hyptosis_grass02.png", "grassTwo", m_clWindow.m_GetWindow());
	m_clTextureManager.m_AddTextureToMap("assets/textures/Grass/hyptosis_grass03.png", "grassThree", m_clWindow.m_GetWindow());

	m_clTextureManager.m_AddTextureToMap("assets/textures/Grass/rpg_grass01.png", "grassFour", m_clWindow.m_GetWindow());
	m_clTextureManager.m_AddTextureToMap("assets/textures/Grass/rpg_grass01.png", "grassFive", m_clWindow.m_GetWindow());

	m_clTextureManager.m_AddTextureToMap("assets/textures/Rock/hyptosis_rock01.png", "rockOne", m_clWindow.m_GetWindow());
	m_clTextureManager.m_AddTextureToMap("assets/textures/Rock/hyptosis_rock02.png", "rockTwo", m_clWindow.m_GetWindow());
	m_clTextureManager.m_AddTextureToMap("assets/textures/Rock/hyptosis_rock03.png", "rockThree", m_clWindow.m_GetWindow());

	m_clTextureManager.m_AddTextureToMap("assets/textures/Water/hyptosis_water01.png", "waterOne", m_clWindow.m_GetWindow());

	m_clTextureManager.m_AddTextureToMap("assets/textures/Objects/Walls/16x16_WoodWall01.png", "woodWallOne", m_clWindow.m_GetWindow());

	m_clTextureManager.m_AddTextureToMap("assets/textures/Objects/Doors/16x16_WoodDoor01.png", "woodDoorOne", m_clWindow.m_GetWindow());

	m_clTextureManager.m_AddTextureToMap("assets/textures/Objects/Wood_Piles/hyptosis_WoodPile01.png", "woodPile", m_clWindow.m_GetWindow());

	m_clTextureManager.m_AddTextureToMap("assets/textures/Objects/Beds/16X16_Bed.png", "bedOne", m_clWindow.m_GetWindow());
}

void Gameloop::m_ResizeAllItems()
{
	m_CreateMainMenuButtons(); 

	m_clResourceManagement.m_CreateActionButtons(m_fWindowWidth, m_fWindowHeight);

	m_clBuildingManager.m_CreateBuildingButtons(m_fWindowWidth, m_fWindowHeight);
}

//--------------------------------------------------------
/*! \fn CheckFramerate : Every frame This will check the current framerate of the game and output it.
*
*/
void Gameloop::m_CheckFramerate(bool print)
{
	m_FrameRate++;

	if (m_FrameRateCounter.getElapsedTime().asSeconds() >= 1)
	{
		m_FrameRateCounter.restart(); 

		if (print)
		{
			std::cout << "Frame Rate : " << m_FrameRate << std::endl;
		}

		m_FrameRate = 0; 
	}
}

//--------------------------------------------------------
/*! \fn Update Delta Time : This will update the current value of delta time; the time since the last frame.
*
*/
void Gameloop::m_UpdateDeltaTime()
{
	m_fDeltaTime = m_DeltaTimer.restart().asSeconds();
}

