/*! \file WoodResource.h
*
* This will be used to create and manage the deployment and maintainment of resources within the game world,
* it will control a single tree on the map. 
*
*/

#pragma once

#include "defs.h"

#include "GameObject.h"
#include "RandGen.h"

/*! \class This will be used to create a single tree in the game world. */
class WoodResource : public GameObject, protected RandGen
{

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	WoodResource();

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~WoodResource();

	// Data Members 

private:

	/*! \var This will be the main tree object which will be displayed. */
	sf::CircleShape m_TreeObject; 

	/*! \var This is the smallest possible radius for the tree. */
	float m_fSmallestRadius; 

	/*! \var This is the largest possible radius for the tree. */
	float m_fLargestRadius; 

	/*! \var This will be the current layer the tree is on. */
	int m_iCurrentLayer; 

	/*! \var This is the current growth for the tree. */
	float m_fCurrentGrowth; 

	/*! \var The preveous radius for the tree. */
	float m_fPreveousRadius; 

	/*! \var Used to check if the tree needs to be cut down. */
	bool m_bCutDownTree = false; 

	/*! \var A timer to limit the amount of growth for the tree. */
	sf::Clock m_GrowthTimer; 

	// Member Functions 

public:

	//--------------------------------------------------------
	//						Setup 
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn Create Tree : This will create a single tree for the game. 
	*Param One : float - The maximum radius for the tree. 
	*Param Two : vector2f - The position for the tree in the game world.
	*Param Three : int - The layer the tree will be placed on. 
	*/
	void m_CreateTree(float radius, sf::Vector2f position, int layer);

	//--------------------------------------------------------
	//						Update
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn Update : This will be used to update the current tree. 
	*
	*/
	void m_Update() override;

	//--------------------------------------------------------
	//						Rendering
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn DrawGameObject : This will allow for the connected class to draw the object onto the game window.
	*Param One : RenderWindow - The current game window.  
	*/
	void m_DrawGameObject(sf::RenderWindow & window) override;

	//--------------------------------------------------------
	/*! \fn DrawFilter : This will be used to choose if the connected object should be drawn onto the game window.
	*Param One : Vector2f - The top left of the game view, limiting the items drawn.
	*Param Two : Vector2f - The bottom right of the game view, limiting the items drawn.
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight) override;

	//--------------------------------------------------------
	/*! \fn DrawFilter (Overload) : This will be used to choose if the connected object should be drawn onto the game window.
	*Param One : Vector2f - The top left of the game view, limiting the items drawn.
	*Param Two : Vector2f - The bottom right of the game view, limiting the items drawn.
	*Param Three : int - The current layer for the tree, limits the draw to a single layer. 
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, int currentLayer);

	//--------------------------------------------------------
	//					Positioning. 
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn SetObjectPos : This will allow for the connected object to set the possition for the object.
	*Param One : float - The X position for the game object. 
	*Param Two : float - The Y position for the game object. 
	*/
	void m_SetObjectPos(float x, float y) override;

	//--------------------------------------------------------
	//					Removing Trees
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn SetTreeCutDown : This will assign This tree to be cut down. 
	*
	*/
	void m_SetTreeCutDown(); 

	//--------------------------------------------------------
	/*! \fn CancelTreeCutDown : This will prevent This tree from being cut down.
	*
	*/
	void m_CancelTreeCutDown(); 

};