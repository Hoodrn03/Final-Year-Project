/*! \file This will hold all of the definitions for the class FontManager. */

#pragma once

#include "defs.h"

/*! \class This will be used to manage all of the fonts which will be used within the game. */
class FontManager
{

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	FontManager(); 

public:
	
	//--------------------------------------------------------
	/*! \fn Deconstructor 
	*
	*/
	~FontManager();

private:

	// Data Members 

	/*! \var This map will hold a font and a string identifier for it. */
	std::map<std::string, sf::Font> m_FontMap; 

public:

	// Member Functions 

	//--------------------------------------------------------\\
	//						Adding Items
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn AddFontToMap : This will allow for new fonts to be added into the map. 
	*Param One : String - The identifier for the new font. 
	*Param Two : Font - The font which will be used for the game.
	*/
	void m_AddFontToMap(std::string filePath, std::string fontName); 

	//--------------------------------------------------------\\
	//						Getting Items
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn GetFontFromMap : Used to get access to a specific font from within the map. 
	*Param One : String - The name of the font you want from the map. 
	*/
	sf::Font m_GetFrontFromMap(std::string fontName); 

};