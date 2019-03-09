/*! \file Cells.h
*
* This will hold the information for a single cell within the game. 
* A group of cells will form a either a row or a column.
*
*/

#pragma once

#include "defs.h"

#include "GameObject.h"

/*! \enum This will be used to set the cells tile */
enum tileSet
{
	_DIRT = 0x2000,		/*!< This will make the tile Dirt. */
	_WATER = 0x3000,	/*!< This will make the tile Water. */
	_ROCK = 0x4000,		/*!< This will make the tile Rock. */
	_SKY = 0x5000,		/*!< This will make the tile Sky. */
	_NO_VALUE			/*!< Base value, This means it has not yet been assigned.  */
};

/*! \enum This will be used to easily distinguish between the different huristic costs for the game. */
enum huristicCost
{
	_DIAGONAL = 14,		/*!< The cost of moving diagonally in A*. */
	_ACROSS = 10		/*!< The cost of moving horizontally in A*. */
};

/*! \struct This will allow for the cell to be given a theoretical position in the grid. */
struct gridPos
{
	float x, y; /*!< The x and y coordinates for This cell object. */
};

/*! \class Cells when grouped up form a grid, each cell will represent a single point within a grid. */
class Cells : public GameObject
{

public: 
	
	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Cells(); 

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor 
	*
	*/
	~Cells();

private:

	// Data Members 

	/*! \var This will be used to display the cell on the screen. */
	sf::RectangleShape m_CellBody; 

	/*! \var This will be used to hold the cells's current center point in world space. */
	sf::Vector2f m_CellCentre; 

	/*! \var The cells unique identifier. */
	int m_iCellId = 0; 

	/*! \var Determines which tile the cell will be displayed as. */
	tileSet m_CurrentTile = _NO_VALUE; 

	/*! \var A list of all the cells around This one Max 8, Min 3. */
	std::vector<Cells*> m_Neighbours; 

	/*! \var This is the cells position within a grid, holds X and Y values.*/
	gridPos m_GridPosition; 

	/*! \var The current layer for This cell object. */
	int m_Layer = 0; 

	/*! \var This will be the default colour codes for water. */
	const sf::Color m_WaterColour = sf::Color(37, 109, 123, 255);

	/*! \var This will be the default colour codes for rock. */
	const sf::Color m_RockColour = sf::Color(90, 77, 65, 255);

	/*! \var This will be the default colour codes for dirt. */
	const sf::Color m_DirtColour = sf::Color(155, 118, 83, 255);

	/*! \var This will be the default colour codes for sky. */
	const sf::Color m_SkyColour = sf::Color(255, 255, 255, 50);

public:

	/*! \var This will hold a reference to a cell that leads to This one. */
	Cells * m_ParentCell = nullptr;

	/*! \var This is the current G Score for This cell. */
	int m_iGScore = 0; 

	/*! \var This is the current H Score for This cell. */
	int m_iHScore = 0; 

	/*! \var This is the current F Score for This cell. */
	int m_iFScore = 0; 

	bool m_bObstruction = false; 

public:

	// Member Functions

	//--------------------------------------------------------\\
	//							Setup 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Create Cell Body : This will be used to initalize This cell. 
	*Param One : Vector2f - The height and width of the cell. 
	*Param Two : Vector2f - The x and y coordinates for the cell. 
	*/
	void m_CreateCellBody(sf::Vector2f dimentions, sf::Vector2f possition); 

	//--------------------------------------------------------
	/*! \fn Create Cell Body (Overload) : This will be used to initalize This cell.
	*Param One : Vector2f - The height and width of the cell.
	*Param Two : Vector2f - The x and y coordinates for the cell.
	*Param Three : int - Red value.
	*Param Four : int - Green value.
	*Param Five : int - Blue value.
	*/
	void m_CreateCellBody(sf::Vector2f dimentions, sf::Vector2f possition, int r, int g, int b);

	//--------------------------------------------------------\\
	//					Positioning
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Check Cell Bounds : This will be used to check if a point is inside This cell. 
	*Param One : float - The x coordine of the point. 
	*Param Two : float - The y coordine of the point.
	*/
	bool m_CheckCellBounds(float x, float y);

	//--------------------------------------------------------
	/*! \fn Set Cell Centre : This will be used to update the current cell centre, using its position and dimentions. 
	*
	*/
	void m_SetCellCentre(); 

	//--------------------------------------------------------
	/*! \fn Set Object Pos : This will place the cell in the game world.
	*Param One : float - x Coordinate.
	*Param Two : float - y Coordinate.
	*/
	void m_SetObjectPos(float x, float y) override;


	//--------------------------------------------------------
	/*! \fn Get Cell Centre : This will return the cells centre point in world space. 
	*
	*/
	sf::Vector2f m_GetCellCentre(); 

	//--------------------------------------------------------\\
	//						Texturing	
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn SetCellColour : This will change the colour of the cell.
	*Param One - int : The amount of red in the cell.
	*Param Two - int : The amount of green in the cell.
	*Param Three - int : The amount of blue in the cell.
	*/
	void m_SetCellColour(int r, int g, int b);

	//--------------------------------------------------------
	/*! \fn Assign Texture : This will be used to change the colour of the cell equil to its assigned tile.
	*
	*/
	void m_AssignColours();

	//--------------------------------------------------------\\
	//						Grid Items 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn SetGridPos : This will be used to assign a position to the cell. 
	*Param One : int - The x position on for the cell on the grid. 
	*Param Two : int - The y position on for the cell on the grid.
	*/
	void m_SetGridPos(int x, int y);

	//--------------------------------------------------------
	/*! \fn GetGridPos : This will return the current position of the cell. 
	*
	*/
	gridPos m_GetGridPos(); 

	//--------------------------------------------------------
	/*! \fn SetLayer : This will allow for the layer of the cell to be set. 
	*
	*/
	void m_SetLayer(int layer); 

	//--------------------------------------------------------
	/*! \fn Get Layer : Will return the value for the layer the cell is currently on. 
	*
	*/
	int m_GetLayer();

	//--------------------------------------------------------
	/*! \fn Assign Neighbour : This will allow for a neighbour to be added to the vector.
	*Param One : Cells - A cell next to This one.
	*/
	void m_AssignNeighbour(Cells &neighbour);

	//--------------------------------------------------------
	/*! \fn Get Neighbours : This will be used to get access to the list of neighbours.
	*
	*/
	std::vector<Cells*> & m_GetNeighbours();

	//--------------------------------------------------------\\
	//						Cell ID
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Get Cell Id : This will be used to read the cell's id.
	*
	*/
	int m_GetCellId();

	//--------------------------------------------------------
	/*! \fn Assign Cell Id : Add a unique identifier to This cell.
	*Param One : int : a number identifier for This cell.
	*/
	void m_AssignCellId(int id);


	//--------------------------------------------------------\\
	//					Tile Settings 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Get Tile : This will be used to check the current tile value for the cell.
	*
	*/
	tileSet m_GetTile();

	//--------------------------------------------------------
	/*! \fn Assign Tile : This will be used to set tile value for This cell.
	*Param One : unsigned int - 1 Dirt, 2 Water, 3 Rock, else null.
	*/
	void m_AssignTile(tileSet whichTile);

	//--------------------------------------------------------\\
	//					Size and Scale 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Get Cell Width : This will return the current width for the cell. 
	*
	*/
	float m_GetCellWidth(); 

	//--------------------------------------------------------
	/*! \fn Get Cell Height : This will return the current height for the cell. 
	*
	*/
	float m_GetCellHeight(); 

	//--------------------------------------------------------\\
	//						Update 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Update : This will be used to update the game logic for This object.
	*
	*/
	void m_Update() override;


	//--------------------------------------------------------\\
	//						Rendering			
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Draw Game Object : Used to draw the cell onto the game window.
	*Param One : RenderWindow - The game window the object is being drawn onto.  
	*/
	void m_DrawGameObject(sf::RenderWindow & window) override; 

	//--------------------------------------------------------
	/*! \fn Draw Filter : This will be used to check if This cell should be draw. 
	*Param One : Vector2f - The top left of the view. 
	*Param Two : Vector2f - The bottom right of the view. 
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight) override; 

};