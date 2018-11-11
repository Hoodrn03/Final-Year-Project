/*! \file RandGen.h
*
* This will allow for the easy generation of random numbers. 
*
*/

#pragma once

#include "defs.h"

/*! \class This class will allow for the generation of random numbers. */
class RandGen
{

	// Data Members

	// Member Functions 

public:

	//--------------------------------------------------------
	/*! \fn GenerateInt : This will be used to generate an int between two values. 
	*Param One : int - The minimum value for the generator to get. 
	*Param One : int - The maximum number for the generator to get. 
	*/
	int m_GenerateInt(int min, int max); 

	int m_GenerateInt(int min, int max, bool print);

};