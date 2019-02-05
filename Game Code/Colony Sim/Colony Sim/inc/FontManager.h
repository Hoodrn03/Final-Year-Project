#pragma once

#include "defs.h"

class FontManager
{

public:

	FontManager(); 

public:
	
	~FontManager();

private:

	// Data Members 

	std::map<std::string, sf::Font> m_FontMap; 

public:

	// Member Functions 

	void m_AddFontToMap(std::string filePath, std::string fontName); 

	sf::Font m_GetFrontFromMap(std::string fontName); 

};