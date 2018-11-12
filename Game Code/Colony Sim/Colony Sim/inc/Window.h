/*! \file Window.h
*
* This class will control all functons regarding the game window and 
* the game view for that window. 
*
*/

#pragma once

#include "defs.h"

/*! \class This will manage and control the window and the view for the game. */
class Window
{

public:
	
	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Window();

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~Window(); 

	// Data Members 

private:

	/*! \var This will be the main game window for the game. */
	sf::RenderWindow m_Window;

	/*! \var This is the game's view, it will act as a camera showing the game world. */
	sf::View m_GameView; 

	/*! \var This will determine the amount the view should move at a given time. */
	const float m_fViewMoveAmount = 2.5f; 

	/*! \var This will be the amount the view will be zoomed by at a single time. */
	const float m_fScrollAmount = 25.f; 

	/*! \var This is the smallest the view will be. */
	const sf::Vector2f m_MinScrollAmount = sf::Vector2f(200, 200); 

	/*! \var This is the largest the view can be. */
	const sf::Vector2f m_MaxScrollAmount = sf::Vector2f(800, 800); 

	/*! \var This is the current move vector for the view, if one of the movement keys is pressed then the 
	*			view will be moved by this vector. 
	*/
	sf::Vector2f m_ViewMoveVector; 

	// Member Functions

public: 

	//--------------------------------------------------------
	/*! \fn InitWindow :- This will create the game window, if there is any errors returns 1 else returns 0; 
	*Param One : int - The width for the game window. 
	*Param Two : int - The height for the game window. 
	*Param Three : string - The name for the window. 
	*/
	int m_InitWindow(int windowWidth, int windowHeight, std::string windowName); 

	//--------------------------------------------------------
	/*! \fn GetWindow : This will return the value of the window, this will for the window to be referenced oustide of the class.
	*
	*/
	sf::RenderWindow & m_GetWindow(); 

	//--------------------------------------------------------
	/*! \fn GetViewUpperBounds : This will return the top left of the game view. 
	*
	*/
	sf::Vector2f m_GetViewUpperBounds(); 

	//--------------------------------------------------------
	/*! \fn GetViewLowerBounds : Thiis will return the bottom right of the game view.  
	*
	*/
	sf::Vector2f m_GetViewLowerBounds(); 

	//--------------------------------------------------------
	/*! \fn CheckForViewMove : This will b eused to check if the view should be moved this frame. 
	*Param One : int - The current key being pressed, if none are pressed it recives 0. 
	*/
	void m_CheckForViewMove(bool upValue, bool downValue, bool leftValue, bool rightValue);

	//--------------------------------------------------------
	/*! \fn Check for View Scroll : This will be used to updte the size of the view based on the direction the mouse wheel is turned.
	*Param One : int - The value for the mouse wheel, it will allow the distinction between up and down, as well as idle. 
	*/
	void m_CheckForViewScroll(int & mouseWheelValue); 

	//--------------------------------------------------------
	/*! \fn MoveViewUp : Moves the view in a direction. 
	*
	*/
	void m_MoveViewUp();

	//--------------------------------------------------------
	/*! \fn MoveViewDown : Moves the view in a direction.
	*
	*/
	void m_MoveViewDown(); 

	//--------------------------------------------------------
	/*! \fn MoveViewLeft : Moves the view in a direction.
	*
	*/
	void m_MoveViewLeft(); 

	//--------------------------------------------------------
	/*! \fn MoveViewRight : Moves the view in a direction.
	*
	*/
	void m_MoveViewRight(); 

};
