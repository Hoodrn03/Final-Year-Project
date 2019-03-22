#pragma once

#include "defs.h"

class InfoWindow
{
public:

	InfoWindow();

	~InfoWindow();

private:

	// Data Members 

	bool m_bDisplayWindow = false;

	sf::RectangleShape m_WindowBody; 

	std::map<std::string, sf::Text*> m_DataMap;

	sf::Font m_LocalFont; 

	std::vector<sf::Text*> v_ListOfData;

public:

	// Member Functions

	void m_SetupInfoWindow(sf::Vector2f dimentions, sf::Vector2f position); 

	void m_DrawInfoWindow(sf::RenderWindow &window); 
	
	void m_AddDataToMap(std::string dataName, int data); 

	void m_AssignFonts(sf::Font newFont); 

	void m_SetDisplay(bool value); 

	void m_UpdateInfoWindow(sf::Vector2f ViewLowerBounds, sf::Vector2f viewSize);

};