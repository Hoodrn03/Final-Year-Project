#pragma once

#include "defs.h"

class TextureManager
{
public:

	TextureManager();

	~TextureManager();

private:

	// Data Members 

	std::map<std::string, sf::Texture> m_TextureMap; 

public:

	// Member Functions

	void m_AddTextureToMap(std::string filePath, std::string name, sf::RenderWindow & window);

	sf::Texture m_GetTextureFromMap(std::string identifier); 

	std::map<std::string, sf::Texture> & m_GetTextureMap();
};