/*! \file Gameloop.h
*
* Component will be used to allow for an objetc to be drawn into the game world
* and also manipulated along the X and Y axis. 
*
*/

#pragma once

#include "defs.h"

class GameObject
{

	// Data Members

protected: 
	
	/*! \var This will store the game objects position. */
	sf::Vector2f m_GameObjectPos; 

	// Member Functions 

public: 

	//--------------------------------------------------------
	/*! \fn DrawGameObject : This will allow for the connected class to draw the object onto the game window.  
	*
	*/
	virtual void m_DrawGameObject(sf::RenderWindow & window) = 0; 

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