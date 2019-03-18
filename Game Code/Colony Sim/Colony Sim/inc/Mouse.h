/*! \file This will manage the main functions for the mouse within the game. */

#pragma once

#include "defs.h"

/*! \class This class will be usd to maintain and manage mouse functions. */
class Mouse
{
	// Constructor 

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Mouse(); 

	// Deconstructor 

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~Mouse(); 

	// Data Members 

private:

	/*! \var This will hold the current position of the mouse in the game window. */
	sf::Vector2f m_MousePos;

	/*! \var This will be used to select items within the game. */
	sf::RectangleShape m_SelectionBox; 

	/*! \var This will be used to limit the mouse down function to once a press. */
	bool m_bMouseFirstDown = false; 

	sf::Font m_LocalFont;

	sf::Text m_ToolTip; 

	std::string m_PreveousText = " "; 

	// Member Functions

public:

	//--------------------------------------------------------
	//						Positioning
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn SetmousePos This will update the current mouse position. 
	*Param One : RenderWindow - The main game window.
	*/
	void m_SetMousePos(sf::RenderWindow &window); 

	//--------------------------------------------------------
	/*! \fn GetMousePos Used to return the value of the mouse position. 
	*
	*/
	sf::Vector2f m_GetMousePos(); 

	//--------------------------------------------------------
	//						Clicking
	//--------------------------------------------------------

	bool m_GetLMBDown(sf::Vector2f mapUpperBounds, sf::Vector2f mapLowerBounds); 

	//--------------------------------------------------------
	//						Selecting
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn CreateSelectionBox : Used to create a selection box when the mouse button is pressed. 
	*
	*/
	void m_CreateSelectionBox(); 

	//--------------------------------------------------------
	/*! \fn GetTopLeftSelectonBox : Used to get check the bounds for the selection box. 
	*
	*/
	sf::Vector2f m_GetTopLeftSelectionBox();

	//--------------------------------------------------------
	/*! \fn GetBottomRightSelectonBox : Used to get check the bounds for the selection box.
	*
	*/
	sf::Vector2f m_GetBottomRightSelectionBox();

	//--------------------------------------------------------
	//						Rendering
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn DrawSelectionBox : Used to draw the box into the game world.
	*Param One : RenderWindow - The main game window. 
	*/
	void m_DrawSelectionBox(sf::RenderWindow &window); 

	//--------------------------------------------------------
	//					Tool Tip Management
	//--------------------------------------------------------
	
	void m_AssignToolTipFont(sf::Font newFont);

	void m_UpdateTooltip(std::string dataToDisplay, sf::Vector2f viewPos, sf::Vector2f viewSize);

	void m_DrawToolTip(sf::RenderWindow & window); 

};