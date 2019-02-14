/*! \file Gameloop.h
*
* Component will be used to allow for an objetc to be drawn into the game world
* and also manipulated along the X and Y axis. 
*
*/

#pragma once

#include "defs.h"

/*! \enum This will determine if the game object will be drawn. */
enum drawItem
{
	_DRAW = 0x101,
	_NO_DRAW = 0x102
};

/*! \class This component will be used to create a game object for the game, it will include methods to draw the object 
*			and manage the position of the game object. 
*/
class GameObject
{

	// Data Members

protected: 
	
	/*! \var This will store the game objects position. */
	sf::Vector2f m_GameObjectPos; 

	/*! \var This is the current status on if the object should be drawn. */
	drawItem m_DrawItem; 

	// Member Functions 

public: 

	//--------------------------------------------------------
	//						Update
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn Update This will be used to update This game object. 
	*
	*/
	virtual void m_Update() = 0; 

	//--------------------------------------------------------
	//						Rendering
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn DrawGameObject : This will allow for the connected class to draw the object onto the game window.  
	*
	*/
	virtual void m_DrawGameObject(sf::RenderWindow & window) = 0; 

	//--------------------------------------------------------
	/*! \fn DrawFilter : This will be used to choose if the connected object should be drawn onto the game window. 
	*Param One : Vector2f - The top left of the game view, limiting the items drawn. 
	*Param Two : Vector2f - The bottom right of the game view, limiting the items drawn.
	*/
	virtual void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight) = 0;

	//--------------------------------------------------------
	//					Positioning
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn SetObjectPos : This will allow for the connected object to set the possition for the object. 
	*
	*/
	virtual void m_SetObjectPos(float x, float y) = 0; 

	//--------------------------------------------------------
	/*! \fn GetObjectPos : This will return the current value for the objects position.
	*
	*/
	sf::Vector2f m_GetObjectPos(); 
};