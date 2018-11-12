/*! \file RandGen.cpp
*
* This will hold all of the definitions for the class RandGen.
*
*/

#include "../inc/RandGen.h"

//--------------------------------------------------------
/*! \fn GenerateInt : This will be used to generate an int between two values.
*Param One : int - The minimum value for the generator to get.
*Param One : int - The maximum number for the generator to get.
*/
int RandGen::m_GenerateInt(int min, int max)
{
	int l_iRandom = 0; 

	// This will generate a number between 0 and max + the minimum value. 

	l_iRandom = rand() % max + min; 

	return l_iRandom;
}

//--------------------------------------------------------
/*! \fn GenerateInt : This will be used to generate an int between two values.
*Param One : int - The minimum value for the generator to get.
*Param Two : int - The maximum number for the generator to get.
*Param Three : bool - True if you want the generated number printed to the console.
*/
int RandGen::m_GenerateInt(int min, int max, bool print)
{
	int l_iRandom = 0;

	// This will generate a number between 0 and max + the minimum value. 

	l_iRandom = rand() % max + min;

	if (print)
	{
		std::cout << "Current Random : " << l_iRandom << std::endl;
	}

	return l_iRandom;
}
