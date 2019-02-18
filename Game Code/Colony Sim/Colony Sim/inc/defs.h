/*! \file defs.h
*
* This file will be used to house all of the included libraries used throughout the project. 
*
*/

#pragma once

// Allows access to sfmls window functions. 
#include <SFML/Graphics.hpp>

#include <SFML/System.hpp>

#include <SFML/Window.hpp>

// Allows for the creation and use of Gui elements works with SFML. 
#include <TGUI/TGUI.hpp>

// Allows for the use of printing to console and other debugging options. 
#include <iostream> 

// Allows for pairs of data to be linked within a map data type. 
#include <map>

// Allows for the use of deques, a storage vector which allows for manipulating elements from both the front and back. 
#include <deque>

// Grants access to more complex math functions, like Atan, exet.
#include <cmath>

// Grants the use of multiple threads; allows for multiple functions to happen at the same time. 
#include <thread>

#ifndef LOOP_TIMEOUT
#define LOOP_TIMEOUT 3000 /*!< This will be used to timeout any function with the possibility of having an infinate loop. */
#endif

/*! \enum Used to allow for actions to be assigned. */
enum currentAction
{
	_NULL = 901,		/*!< This is used when there is no other actions. */
	_CUT_TREES = 903	/*!< This will allow for tree cutting to be assigned. */
};

