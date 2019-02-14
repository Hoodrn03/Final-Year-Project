/*! \file This will be used to controla and maintain all of the user interface object for the game. */

#pragma once

#include "defs.h"

/*! \class This will hold all of the user interface items to be used by the game. */
class UserInterface
{
public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	UserInterface();

public: 

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~UserInterface();

private:

	// Data Members 

	/*! \var The main Gui object. It will hold all of the other widgets for the game. */
	tgui::Gui m_Gui; 

public:

	// Member Functions 

	//--------------------------------------------------------
	//						Setup 
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn InitGui : Used to create the Gui object. 
	*Param One : RenderWindow - The main game window to attach the Gui to. 
	*/
	void m_InitGui(sf::RenderWindow &window); 

	//--------------------------------------------------------
	//					Handle Events 
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn HandleEvents : This will allow for the Gui to handle events such as button presses. 
	*Param One : Event - The current event buffer variable. 
	*/
	void m_HandleEvents(sf::Event &ThisEvent);

	//--------------------------------------------------------
	//						Rendering
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn DrawGui : This will draw the Gui onto the game window.  
	*
	*/
	void m_DrawGui();

	//--------------------------------------------------------
	//					Adding to Gui 
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn AddWidget : This will allow for a widget to be added into the Gui. 
	*Param One : Button - The button you want to add. 
	*/
	void m_AddWidget(tgui::Button::Ptr &buttonToAdd); 

	//--------------------------------------------------------
	/*! \fn AddWidget : This will allow for a list of widgets to be added into the Gui.
	*Param One : vector<Button> - A list of buttons you want to add.
	*/
	void m_AddWidget(std::vector<tgui::Button::Ptr> &buttonsToAdd);

	//--------------------------------------------------------
	//					Removing from Gui 
	//--------------------------------------------------------

	//--------------------------------------------------------
	/*! \fn RemoveWidget : Used to remove a single or list of widgets from the Gui. 
	*Param One : Button - A button to remove. 
	*/
	void m_RemoveWidget(tgui::Button::Ptr &buttonToRemove);

	//--------------------------------------------------------
	/*! \fn RemoveWidget : Used to remove a single or list of widgets from the Gui.
	*Param One : vector<Button> - A list of buttons to remove. 
	*/
	void m_RemoveWidget(std::vector<tgui::Button::Ptr> &buttonToRemove);
	
	//--------------------------------------------------------
	/*! \fn ClearAllWidgets : USed to empty the Gui of all its current widgets. 
	*
	*/
	void m_ClearAllWidgets(); 

};