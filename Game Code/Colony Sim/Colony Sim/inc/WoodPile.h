#pragma once

#include "defs.h"

#include "Cells.h"
#include "RandGen.h"

class WoodPile : public GameObject, public RandGen
{
public:

	WoodPile();

	~WoodPile(); 

	// Data Members 

private:

	Cells * m_CurrentCell; 

	sf::Font m_CurrentFont; 

	sf::Text m_PileCount; 

	sf::RectangleShape m_PileBody; 

	int m_iNumberOfWood = 0; 

	const int m_iMaxWood = 150; 

	// Member Functions 

public:

	//--------------------------------------------------------
	//						Setup 
	//--------------------------------------------------------

	void m_InitWoodPile(Cells * pileLocation, sf::Font newFont, float currentGrowth);

	//--------------------------------------------------------
	//						Update
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn Update This will be used to update This game object.
	*
	*/
	void m_Update();

	//--------------------------------------------------------
	//						Rendering
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn DrawGameObject : This will allow for the connected class to draw the object onto the game window.
	*
	*/
	void m_DrawGameObject(sf::RenderWindow & window);

	//--------------------------------------------------------
	/*! \fn DrawFilter : This will be used to choose if the connected object should be drawn onto the game window.
	*Param One : Vector2f - The top left of the game view, limiting the items drawn.
	*Param Two : Vector2f - The bottom right of the game view, limiting the items drawn.
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	//--------------------------------------------------------
	//					Positioning
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn SetObjectPos : This will allow for the connected object to set the possition for the object.
	*
	*/
	void m_SetObjectPos(float x, float y);

	//--------------------------------------------------------
	/*! \fn GetObjectPos : This will return the current value for the objects position.
	*
	*/
	sf::Vector2f m_GetObjectPos();

};