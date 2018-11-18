/*! \file Grid.h
*
* This class will be used to create a grid with a definable number of rows, columns and layers,
* this grid will need to be placed within a rectangle shape.  
*
*/

#pragma once

#include "defs.h"

#include "Cells.h"
#include "RandGen.h"


/*! \class This will be used to create a gird within a rectangle shape, this will allow for a definition of rows, columns,
*			as well as a number of layers. 
*/
class Grid : public RandGen
{

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Grid();

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~Grid();

private:

	// Data Members 

	/*! \var This is the completed grid, it has three layers for the three dimentions of the grid; 
	*			Z (layers), X (rows) and Y (columns). There will only every be a single instance of the 
	*			grid in the game. 
	*/
	std::vector<std::vector<std::vector<Cells>>> m_Grid; 

public:

	// Member Functions 

	//--------------------------------------------------------
	/*! \fn CreateGrid : This will be used to initalize the grid. 
	*Param One : int - The number of rows for the grid.
	*Param Two : int - The number of columns for the grid. 
	*Param Three : int - The number of layers on the grid. 
	*Param Four : RectangleShape : The location and size for the grid, the grid is placed inside the rectangle shape. 
	*/
	void m_CreateGrid(unsigned int rows, unsigned int columns, unsigned int layers, sf::RectangleShape gridLocation);

	//--------------------------------------------------------
	/*! \fn AssignNeighbours : This will be used to give all of the cells within the grid their neighbours. 
	*
	*/
	void m_AssignNeighbours(); 

	//--------------------------------------------------------
	/*! \fn CreateLake : This will be used to generate a lake within the grid. 
	*Param One : int - The x position of the start cell. 
	*Param Two : int - The y position of the start cell. 
	*Param Three : int - The layer which the lake should be generated. 
	*Param Four : int - The number of iterations the function should take while making the lake. 
	*/
	void m_CreateLake(int cellX, int cellY, int layer, int numberOfIterations);

	//--------------------------------------------------------
	/*! \fn CreateRiver : This will be used to create a river in the grid. 
	*Param One : Vector<Cells> - A path of cells the river should be generated along. 
	*Param Two : int - The width in cells the river should be. 
	*Param Three : int - The layer the river should be generated on.
	*/
	void m_CreateRiver(std::vector<Cells*> riverPath, int riverWidth, int layer);

	//--------------------------------------------------------
	/*! \fn Create Underground Water : This will be used to create water for layers under the gound level. 
	*Param One : int - The lowest layer for the water to be placed on. 
	*Param Two : int - The highest layer for the water to be placed on. 
	*/
	void m_CreateUndergroundWater(int minLayer, int maxLayer); 

	//--------------------------------------------------------
	/*! \fn Create Rock : This will be used to assign cells to be rock tiles. 
	*Param One : int - Which layer on the map the rock should be assigned to. 
	*/
	void m_CreateRock(int layer); 

	//--------------------------------------------------------
	/*! \fn Create Underground Rock : This will create rock for layers under the ground level. 
	*Param One : int - The lowest layer for the rock to be placed on. 
	*Param Two : int - The highest layer for the rock to be placed on. 
	*/
	void m_CreateUndergroundRock(int minLayer, int maxLayer);

	//--------------------------------------------------------
	/*! \fn Create Upper Rock : This will be used to create rock cells above the ground level. 
	*Param One : int - The lowest layer for the rock to be placed on. 
	*Param Two : int - The highest layer for the rock to be placed on. 
	*/
	void m_CreateUpperRock(int minLayer, int maxLayer);

	//--------------------------------------------------------
	/*! \fn Create Dirt : This will fill in the remaning tiles on the map with dirt, used last in the generation process. 
	*Param One : int - Which layer on the map the dirt should be assigned to.
	*/
	void m_CreateDirt(int layer); 

	//--------------------------------------------------------
	/*! \fn Create Underground Dirt : This will be used to fill the remaning underground tiles with dirt. 
	*Param One : int - The lowest layer for the dirt to be placed on.
	*Param Two : int - The highest layer for the dirt to be placed on.
	*/
	void m_CreateUndergroundDirt(int minLayer, int maxLayer); 

	//--------------------------------------------------------
	/*! \fn Create Sky : This will be used to fill the remaning above ground tiles with sky tiles. 
	*Param One : int - The lowest layer for the sky to be placed on.
	*Param Two : int - The highest layer for the sky to be placed on.
	*/
	void m_CreateSky(int minLayer, int maxLayer);

	//--------------------------------------------------------
	/*! \fn AssignTextures : This will be used to give all of the cell's textures, or change the cell's colours. 
	*
	*/
	void m_AssignTextures(); 

	//--------------------------------------------------------
	/*! \fn GetCell : This will be used to get access to a specific cell.
	*Param One : int - The layer of the cell.
	*Param Two : int - The X for the cell.
	*Param Three : int - The Y for the cell. 
	*/
	Cells * m_GetCell(int layer, int x, int y); 

	Cells * m_GetRandomDirtCell(int layer); 

	Cells * m_ConvertWorldPosToGridPos(sf::Vector2f currentPos); 

	//--------------------------------------------------------
	/*! \fn DrawGrid : This will be used to draw the grid. 
	*Param One : renderwindow - The main game window the grid should be drawn onto. 
	*Param Two : int - The layer of the grid to be drawn. 
	*/
	void m_DrawGrid(sf::RenderWindow & window, unsigned int layer); 

	//--------------------------------------------------------
	/*! \fn CheckItemsForRender : This will be used to limit the items to be drawn. 
	*Param One : vector2f - The top left of the view. 
	*Param Two : vector2f - The bottom right of the view. 
	*Param Three : int - The layer of items to draw. 
	*/
	void m_CheckItemsForRender(sf::Vector2f topLeft, sf::Vector2f bottomRight, unsigned int layer);

	//--------------------------------------------------------
	/*! \fn GetNumberOfLayers : This will be used to check the number of layers on the grid. 
	*
	*/
	unsigned int m_GetNumberOfLayers(); 

	//--------------------------------------------------------
	/*! \fn GetNumberOfRows : This will be used to check the number of rows on the grid. 
	*
	*/
	unsigned int m_GetNumberOfRows();

	//--------------------------------------------------------
	/*! \fn GetNumberOfColumns : This will be used to check the number of columns on the grid. 
	*
	*/
	unsigned int m_GetNumberOfColumns(); 

};

