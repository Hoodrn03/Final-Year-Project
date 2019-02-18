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

	// Setup window variables. 
	m_clWindow.m_GetWindow().setKeyRepeatEnabled(false);

	m_clWindow.m_GetWindow().setFramerateLimit(60);

	// Init Gui
	m_clUserInterface.m_InitGui(m_clWindow.m_GetWindow());

	m_MainMenu(); 

	return 0;

}

tgui::Button::Ptr Gameloop::m_CreateExitButton()
{
	tgui::Button::Ptr  l_ExitButton = tgui::Button::create();

	l_ExitButton->setSize(100, 50);
	l_ExitButton->setPosition(100, 100);
	l_ExitButton->setInheritedFont(m_clFontManager.m_GetFrontFromMap("arial"));
	l_ExitButton->setText("Exit");

	// Use a lambda function to add a small operation to the button when it is pressed. 
	l_ExitButton->connect("Pressed", [&]() {m_clWindow.m_GetWindow().close();  });

	return l_ExitButton;
}

tgui::Button::Ptr Gameloop::m_CreateBeginButton()
{
	tgui::Button::Ptr  l_BeginButton = tgui::Button::create();

	l_BeginButton->setSize(100, 50);
	l_BeginButton->setPosition(100, 200);
	l_BeginButton->setInheritedFont(m_clFontManager.m_GetFrontFromMap("arial"));
	l_BeginButton->setText("Begin");

	// Use a lambda function to add a small operation to the button when it is pressed. 
	l_BeginButton->connect("Pressed", [&]() {m_BeginGame();  });

	return l_BeginButton;
}


int Gameloop::m_MainMenu()
{
	// TEMP Start game 

	m_BeginGame(); 

	// Init pregame logic. 

	m_clUserInterface.m_ClearAllWidgets(); 

	// Add buttons into the UI. 

	m_clUserInterface.m_AddWidget(m_CreateExitButton()); 

	m_clUserInterface.m_AddWidget(m_CreateBeginButton()); 

	// Start Game Loop. 

	while (m_clWindow.m_GetWindow().isOpen())
	{
		// Update additional logic at the beginning of the frame. 

		m_CheckFramerate();

		m_UpdateDeltaTime();

		// Handle Events. 
		m_clEventHandler.m_CheckForEvents(m_clWindow.m_GetWindow());

		m_clUserInterface.m_HandleEvents(m_clEventHandler.m_GetEvent());

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
	m_clMap.m_SetUpGameMap(sf::Vector2f(800, 800), sf::Vector2f(0, 0));

	// Add colonists. 
	m_clColonistManager.m_AddColonist(1, sf::Vector2f(5, 5), m_clMap.m_GetGrid(), m_clMap.m_GetGroundLevel());

	// Add resources. 
	m_clResourceManagement.m_AddTrees(30, 10.f, m_clMap.m_GetGroundLevel(), m_clMap.m_GetGrid());

	// Prepare buttons 

	m_clColonistManager.m_CreateColonistActionButtons(m_clFontManager.m_GetFrontFromMap("arial"), m_clWindow.m_GetWindow());

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

		m_CheckFramerate(); 

		m_UpdateDeltaTime(); 

		// Update Mouse. 
		m_clMouse.m_SetMousePos(m_clWindow.m_GetWindow());

		m_clMouse.m_CreateSelectionBox();

		// Handle Events. 
		m_clEventHandler.m_CheckForEvents(m_clWindow.m_GetWindow());

		if (!m_clWindow.m_GetWindow().isOpen())
		{
			// Check the state of the game window and join all threads if needed. 

			l_First.join(); 
		}

		m_clUserInterface.m_HandleEvents(m_clEventHandler.m_GetEvent()); 

		// Update the game window.
		m_clWindow.m_CheckForViewMove(m_clEventHandler.m_CheckViewUpValue(), m_clEventHandler.m_CheckViewDownValue(), m_clEventHandler.m_CheckViewLeftValue(), m_clEventHandler.m_CheckViewRightValue()); 

		m_clWindow.m_CheckForViewScroll(m_clEventHandler.m_GetMouseWheelState());

		// Update the game map. 
		m_clMap.m_CheckForLayerChange(m_clEventHandler.m_CurrentLayerChangeValue());

		m_clMap.m_Update(); 

		// Update the game resources. 
		m_clResourceManagement.m_Update(); 

		m_clResourceManagement.m_AssignAction(m_clEventHandler.m_GetCurrentAction());

		m_clResourceManagement.m_SelectResources(m_clMouse.m_GetTopLeftSelectionBox(), m_clMouse.m_GetBottomRightSelectionBox()); 

		// Update colonists. 
		m_clColonistManager.m_Update(m_clMap.m_GetGrid()); 

		m_clColonistManager.m_SelectColonist(m_clMouse.m_GetTopLeftSelectionBox(), m_clMouse.m_GetBottomRightSelectionBox(), sf::Mouse::isButtonPressed(sf::Mouse::Right)); 

		m_clColonistManager.m_CheckForSelected(); 

		if (m_clColonistManager.m_bColonistSelected == true)
		{
			if (m_clColonistManager.m_bButtonsCreated == false)
			{
				m_clUserInterface.m_AddWidget(m_clColonistManager.v_ListOfButtons);

				m_clColonistManager.m_bButtonsRemoved = false;

				m_clColonistManager.m_bButtonsCreated = true;
			}
		}
		else
		{
			if (m_clColonistManager.m_bButtonsRemoved == false)
			{
				m_clUserInterface.m_RemoveWidget(m_clColonistManager.v_ListOfButtons);

				m_clColonistManager.m_bButtonsRemoved = true;

				m_clColonistManager.m_bButtonsCreated = false;
			}
		}

		// Draw Items. 
		m_RenderGame();
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

		m_clColonistManager.m_Pathfinding(m_clMap.m_GetGrid(), m_clResourceManagement);
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

	// Draw the colonists at the top.
	m_clColonistManager.m_Render(m_clWindow.m_GetWindow()); 

	// Draw UI above the other game elements. 

	m_clMouse.m_DrawSelectionBox(m_clWindow.m_GetWindow()); 

	m_clUserInterface.m_DrawGui(); 

	// Display new objects. 
	m_clWindow.m_GetWindow().display(); 
}

//--------------------------------------------------------
/*! \fn CheckFramerate : Every frame This will check the current framerate of the game and output it.
*
*/
void Gameloop::m_CheckFramerate()
{
	m_FrameRate++;

	if (m_FrameRateCounter.getElapsedTime().asSeconds() >= 1)
	{
		m_FrameRateCounter.restart(); 

		std::cout << "Frame Rate : " << m_FrameRate << std::endl;

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

