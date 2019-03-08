#pragma once

#include "defs.h"

#include "BuildingObject.h"

class BuildingManager
{
public:

	BuildingManager();

	~BuildingManager();

private:

	// Data Members 

	std::vector<BuildingObject> v_Buildings; 

	sf::Font m_LocalFont;

	std::vector<tgui::Button::Ptr> v_BuildingButtons; 

	bool m_bBuildObject = false; 

	std::string m_sCurrentObjectToBuild = "Null"; 

	sf::RectangleShape m_PlaceholderBuilding; 

	float m_fBuildingWidth, m_fBuildingHeight; 

public:

	tgui::Button::Ptr m_BuildingActionButton;

	bool m_bDisplayButtons = false;

	bool m_bButtonsCreated = false;

	bool m_bButtonsRemoved = false;

public:

	// Member Functions 

	void m_Setup(); 

	void m_Setup(sf::Vector2f cellSize);

	void m_AddBuilding(std::string buildingType); 

	void m_AssignFont(sf::Font mainFont);

	void m_Update(sf::Vector2f mousePos);

	void m_Update(sf::Vector2f mousePos, bool mouseDown);

	void m_DrawBuildings(sf::RenderWindow &window); 

	void m_DrawFilter(); 

	void m_CreateBuildingButtons(float windowWidth, float windowHeight);

	void m_SetBuildObjects(bool buildNewObjects); 

	void m_SetCurrentObjectToBuild(std::string buildingType); 

	void m_DrawBuildingButtons();

	std::vector<tgui::Button::Ptr> m_GetBuildingButtons();

};