#include "BuildingManager.h"

BuildingManager::BuildingManager()
{
}

BuildingManager::~BuildingManager()
{
}

void BuildingManager::m_Setup()
{
	m_PlaceholderBuilding.setSize(sf::Vector2f(50, 50));
	m_PlaceholderBuilding.setOrigin(m_PlaceholderBuilding.getGlobalBounds().width * 0.5f, m_PlaceholderBuilding.getGlobalBounds().height * 0.5f); 
	m_PlaceholderBuilding.setFillColor(sf::Color::Transparent);
	m_PlaceholderBuilding.setOutlineColor(sf::Color::White);
	m_PlaceholderBuilding.setOutlineThickness(0.5f);
}

void BuildingManager::m_Setup(sf::Vector2f cellSize)
{
	m_fBuildingWidth = cellSize.x;
	m_fBuildingHeight = cellSize.y; 

	m_PlaceholderBuilding.setSize(sf::Vector2f(m_fBuildingWidth, m_fBuildingHeight));
	m_PlaceholderBuilding.setOrigin(m_PlaceholderBuilding.getGlobalBounds().width * 0.5f, m_PlaceholderBuilding.getGlobalBounds().height * 0.5f);
	m_PlaceholderBuilding.setFillColor(sf::Color::Transparent);
	m_PlaceholderBuilding.setOutlineColor(sf::Color::White);
	m_PlaceholderBuilding.setOutlineThickness(0.5f);
}

void BuildingManager::m_AddBuilding(std::string buildingType)
{
	BuildingObject l_TempBuilding; 

	l_TempBuilding.m_SetupBuildingObject(sf::Vector2f(m_fBuildingWidth, m_fBuildingHeight), m_PlaceholderBuilding.getPosition(), buildingType);

	v_Buildings.push_back(l_TempBuilding); 

}

void BuildingManager::m_AssignFont(sf::Font mainFont)
{
	m_LocalFont = mainFont; 
}

void BuildingManager::m_Update(sf::Vector2f mousePos)
{
	if (m_bBuildObject == true)
	{
		m_PlaceholderBuilding.setPosition(mousePos); 
	}
}

void BuildingManager::m_Update(sf::Vector2f mousePos, bool mouseDown)
{
	if (m_bBuildObject == true)
	{
		m_PlaceholderBuilding.setPosition(mousePos);

		if (mouseDown == true)
		{
			bool l_bAlreadyThere = false; 

			for (unsigned int i = 0; i < v_Buildings.size(); i++)
			{
				if (v_Buildings[i].m_CheckBuildingBounds(mousePos.x, mousePos.y))
				{
					l_bAlreadyThere = true; 

					// std::cout << "Building already there" << std::endl;
				}
			}

			if (l_bAlreadyThere == false)
			{
				// std::cout << "Placing " << m_sCurrentObjectToBuild << std::endl;

				m_AddBuilding(m_sCurrentObjectToBuild);
			}
		}
	}
}

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

void BuildingManager::m_DrawFilter()
{
}

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

void BuildingManager::m_SetBuildObjects(bool buildNewObjects)
{
	m_bBuildObject = buildNewObjects; 
}

void BuildingManager::m_SetCurrentObjectToBuild(std::string buildingType)
{
	m_sCurrentObjectToBuild = buildingType; 
}

void BuildingManager::m_DrawBuildingButtons()
{
	m_bDisplayButtons = !m_bDisplayButtons;
}

std::vector<tgui::Button::Ptr> BuildingManager::m_GetBuildingButtons()
{
	m_bButtonsCreated = !m_bButtonsCreated;

	return v_BuildingButtons; 
}
