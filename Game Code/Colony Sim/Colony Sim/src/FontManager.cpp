#include "FontManager.h"

FontManager::FontManager()
{
	std::cout << "------------------------------------------" << "\nLoading Fonts into map. " << std::endl;

	m_AddFontToMap("assets/fonts/arial.ttf", "arial");

	std::cout << "------------------------------------------" << std::endl;
}

FontManager::~FontManager()
{
}

void FontManager::m_AddFontToMap(std::string filePath, std::string fontName)
{
	if (m_FontMap.count(fontName) > 0)
	{
		std::cout << "Font already in map" << std::endl;
	}

	else 
	{
		sf::Font l_FontToLoad;

		if (!l_FontToLoad.loadFromFile(filePath))
		{
			std::cout << "Unable To load Font : " << fontName << ", from " << filePath << std::endl;
		}

		else
		{
			m_FontMap.insert(std::pair<std::string, sf::Font>(fontName, l_FontToLoad));

			std::cout << "Loaded " << fontName << " from " << filePath << " successfully." << std::endl;
		}
	}
}

sf::Font FontManager::m_GetFrontFromMap(std::string fontName)
{
	if (m_FontMap.count(fontName) > 0)
	{
		return m_FontMap.find(fontName)->second; 
	}
	else
	{
		return sf::Font(); 
	}
}