
#include "../inc/RandGen.h"



int RandGen::m_GenerateInt(int min, int max)
{
	int l_iRandom = 0; 

	// This will generate a number between 0 and max + the minimum value. 

	l_iRandom = rand() % max + min; 

	std::cout << "Current Random : " << l_iRandom << std::endl;

	return l_iRandom;
}
