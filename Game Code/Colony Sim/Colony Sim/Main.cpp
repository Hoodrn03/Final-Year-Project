/*! \file Main.cpp
*
* The entry point for the program. 
*
*/

#include "GameLoop.h"

int main()
{
	Gameloop l_clGameLoop; 

	if (l_clGameLoop.m_SetUp() != 0)
	{
		std::cout << "Error setting up game" << std::endl;

		return 1;
	}

	l_clGameLoop.m_Update(); 

	return 0; 
}