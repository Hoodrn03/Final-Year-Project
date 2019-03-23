#include "InfoWindow.h"

InfoWindow::InfoWindow()
{
}

InfoWindow::~InfoWindow()
{
	if (v_ListOfData.size() > 0)
	{
		for (unsigned int i = 0; i < v_ListOfData.size(); i++)
		{
			delete v_ListOfData[i];
		}
	}
}

void InfoWindow::m_SetupInfoWindow(sf::Vector2f dimentions, sf::Vector2f position)
{
	m_WindowBody.setSize(dimentions); 

	m_WindowBody.setPosition(position); 

	m_WindowBody.setFillColor(sf::Color(211, 211, 211, 255));
}

void InfoWindow::m_DrawInfoWindow(sf::RenderWindow & window)
{

	if (m_bDisplayWindow == true)
	{
		window.draw(m_WindowBody);

		if (v_ListOfData.size() > 0)
		{
			for (unsigned int i = 0; i < v_ListOfData.size(); i++)
			{
				if (v_ListOfData[i]->getFont() == nullptr)
				{
					break;
				}
				else
				{
					window.draw(*v_ListOfData[i]);
				}
			}
		}
	}
}

void InfoWindow::m_AddDataToMap(std::string dataName, int data)
{
	if (m_DataMap.count(dataName) > 0)
	{
		// std::cout << "Already Inside" << std::endl;

		if (data >= 0)
		{
			m_DataMap[dataName]->setString(dataName + " " + std::to_string(data));
		}
		else
		{
			m_DataMap[dataName]->setString(dataName);
		}

	}
	else
	{
		sf::Text * l_TempText = new sf::Text;

		l_TempText->setFont(m_LocalFont);

		if (data >= 0)
		{
			l_TempText->setString(dataName + " " + std::to_string(data));
		}
		else
		{
			l_TempText->setString(dataName);
		}

		l_TempText->setPosition(m_WindowBody.getPosition() + sf::Vector2f(0, (float)(l_TempText->getCharacterSize() * v_ListOfData.size())));

		l_TempText->setFillColor(sf::Color::Black);

		l_TempText->setCharacterSize(15);

		v_ListOfData.push_back(l_TempText);

		std::pair<std::string, sf::Text*> l_TempPair;

		l_TempPair.first = dataName;

		l_TempPair.second = l_TempText;

		m_DataMap.insert(l_TempPair);

	}
}

void InfoWindow::m_AssignFonts(sf::Font newFont)
{
	m_LocalFont = newFont; 
}

void InfoWindow::m_SetDisplay(bool value)
{
	m_bDisplayWindow = value; 
}

void InfoWindow::m_UpdateInfoWindow(sf::Vector2f ViewLowerBounds, sf::Vector2f viewSize)
{
	m_WindowBody.setPosition(ViewLowerBounds - sf::Vector2f(m_WindowBody.getGlobalBounds().width, m_WindowBody.getGlobalBounds().height));

	m_WindowBody.setSize(sf::Vector2f(viewSize.x * 0.4f, viewSize.y * 0.3f));

	if (v_ListOfData.size() > 0)
	{
		for (unsigned int i = 0; i < v_ListOfData.size(); i++)
		{
			v_ListOfData[i]->setCharacterSize(viewSize.y * 0.04f);

			v_ListOfData[i]->setPosition(m_WindowBody.getPosition() + sf::Vector2f(0, (float)(v_ListOfData[i]->getCharacterSize() * i)));

		}
	}
}


