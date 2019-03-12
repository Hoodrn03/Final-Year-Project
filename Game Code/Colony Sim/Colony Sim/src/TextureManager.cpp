#include "TextureManager.h"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
}

void TextureManager::m_AddTextureToMap(std::string filePath, std::string name, sf::RenderWindow & window)
{
	if (window.isOpen())
	{

		if (m_TextureMap.count(name) > 0)
		{
			std::cout << "Texture already in map" << std::endl;
		}

		else
		{
			sf::Texture l_TextureToLoad;

			if (!l_TextureToLoad.loadFromFile(filePath))
			{
				std::cout << "Unable To load Texture : " << name << ", from " << filePath << std::endl;
			}

			else
			{
				m_TextureMap.insert(std::pair<std::string, sf::Texture>(name, l_TextureToLoad));

				std::cout << "------------------------------------------" << "\nLoading Textures into map. " << std::endl;

				std::cout << "Loaded " << name << " from " << filePath << " successfully." << std::endl;
			}
		}
	}
}

sf::Texture TextureManager::m_GetTextureFromMap(std::string identifier)
{
	if (m_TextureMap.count(identifier) > 0)
	{
		return m_TextureMap.find(identifier)->second;
	}
	else
	{
		return sf::Texture();
	}
}
