/*! \file Colonist.h
*
* This class holds all of the functionality for the colonists, it will allow for them to move freely 
* around the game map, as well as allowing for them to manipulate the game world under the player's commands. 
*
*/

#pragma once

#include "defs.h"

#include "GameObject.h"
#include "Pathfinding.h"
#include "Cells.h"

#include "WoodResource.h"
#include "BuildingObject.h"

#include "InfoWindow.h"

/*! \enum This will hold the name for the job the colonist currently has. */
enum job
{
	_IDLE = 0x235,			/*< This will be the default job for each colonist. */
	_LOGGING = 236,			/*< This will enable the colonist to cut trees in the game world. */
	_CONSTRUCTION = 237		/*!< This will allow for the colonist to build buildings within the world. */
};

/*! \class This class will hold the functionality for a single colonist within the game. */
class Colonist : public GameObject, public InfoWindow
{

public:

	//--------------------------------------------------------
	/*! \fn Constructor
	*
	*/
	Colonist();

public:

	//--------------------------------------------------------
	/*! \fn Deconstructor
	*
	*/
	~Colonist();

	// Data Members 

private:

	/*! \var This will be the colonist's main body within the game. */
	sf::RectangleShape m_ColonistBody;

	/*! \var This will be used to show when the colonist is selected by the player. */
	sf::CircleShape m_SelectedCircle;

	/*! \var Will be used to genearte a new path for the colonist,if they have reached the end of their current one. */
	bool m_bFindNewPath = true;

	/*! \var This will be the current cell on the grid the colonist is currently inside. */
	Cells * m_CurrentCell = nullptr;

	Cells * m_EndCell = nullptr;

	WoodResource * m_TargetTree = nullptr;

	BuildingObject * m_TargetBuild = nullptr;


	InfoWindow m_clInfoWindow;

	/*! \var This will be used to keep track of which layer the colonist is currently on. */
	unsigned int m_iCurrentLayer;

	/*! \var This will be used to update the colonist's current position along their path. */
	unsigned int m_iCurrentMoveTo = 0;

	/*! \var This will be used to limit when the colonist will move in the game. */
	sf::Clock m_MovementClock;

	sf::Clock m_WorkTimer;

	/*! \var The time (in seconds) when the colonist will move. */
	const float m_fmovementTimer = 0.5f;

	/*! \var This is a list of cells the pathfinding algorithm will have returned. It will allow for the colonist to move. */
	std::deque<Cells*> m_Path;

	/*! \var A line displaying the path the colonist is moving along. */
	sf::VertexArray m_PathLine;

	/*! \var This is a list of tiles which will act as obsticales for the colonist.
	*			This will prevent the colonist from generating a path through these cells.
	*/
	std::vector<tileSet> m_Obstructions = { _ROCK, _SKY };

	/*! \var The current job the colonist is performing. */
	job m_CurrentJob = _IDLE;

	/*! \var This is used to tell when the colonist is selected. */
	bool m_bSelected = false;

	bool m_bFoundTree = false;

	bool m_bAtTree = false;

	sf::Font m_LocalFont; 

	std::pair<std::string, int> m_SleepData; 

public:

	unsigned int m_iCurrentWood = 0; 

	int m_iNeededWood = 0; 

	unsigned int m_iIdleCounter = 0;

	// Member Functions 

public:

	//--------------------------------------------------------\\
	//							Setup 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Create Colonist Body (Overload) : This will be used to initalize the rectangle shape dor what will become the colonist. 
	*Param One : Vector2f - This will be the dimentions for the colonist.
	*Param Two : Cells - The cell the colonist will start in. 
	*/
	int m_CreateColonistBody(sf::Vector2f dimentions, Cells * currentCell);

	void m_AssignColonistFont(sf::Font &newFont);

	//--------------------------------------------------------\\
	//							Update 
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Update Current Cell : This will be used to assign the colonist a new current cell.
	*Param One : Cells - This will be the new value for the current cell. 
	*/
	void m_UpdateCurrentCell(Cells * newCurrentCell);

	//--------------------------------------------------------
	/*! \fn Update : This will be used to update the logic for This class. 
	*
	*/
	void m_Update() override; 

	void m_UpdateInfoWindow(sf::Vector2f viewLowerBounds, sf::Vector2f viewSize);

	//--------------------------------------------------------\\
	//						Job System
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Set Job : This will be used to assign a new job to This colonist. 
	*Param One : job - This is the new job for This colonist. 
	*/
	void m_SetJob(job newJob);

	//--------------------------------------------------------
	/*! \fn Idle Job : A job for the colonist without them actually doing anything. 
	*
	*/
	void m_IdleJob(); 

	//--------------------------------------------------------
	/*! \fn Cut Trees : This will allow for the colonist to remove trees in the game world. 
	*
	*/
	void m_CutTrees(); 

	void m_BuildBuilding(); 

	//--------------------------------------------------------
	/*! \fn Get Current Job : Will be used to get the value of the current job the colonist is performing.
	*
	*/
	job m_GetCurrentJob();

	void m_SetNeededWood(float woodNeeded); 

	//--------------------------------------------------------\\
	//						Rendering
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Draw Game Object : This will be used to render the colonist. 
	*Param One : RenderWindow - The current game widow for the object to be drawn onto. 
	*/
	void m_DrawGameObject(sf::RenderWindow & window) override;

	//--------------------------------------------------------
	/*! \fn Draw Filter : This will be used to filter This object for draing, used to limit the amount drawn onto the screen at a given time. 
	*Param One : Vector2f - The top left corner of the game view. 
	*Param Two : Vector2f - The bottom right corner of the game view. 
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight) override;

	//--------------------------------------------------------
	/*! \fn Draw Filter (Overload) : This will be used to filter This object for draing, used to limit the amount drawn onto the screen at a given time.
	*Param One : Vector2f - The top left corner of the game view.
	*Param Two : Vector2f - The bottom right corner of the game view.
	*Param Three : unsinged int - The current layer the displayed on the game window. 
	*/
	void m_DrawFilter(sf::Vector2f topLeft, sf::Vector2f bottomRight, unsigned int currentLayer);

	//--------------------------------------------------------\\
	//						Positioning
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Set Object Pos : This will be used to update the current position of the game object. 
	*Param One : float - The new X for the object. 
	*Param Two : float - The new Y for the object.
	*/
	void m_SetObjectPos(float x, float y) override;

	//--------------------------------------------------------
	/*! \fn Set Current Layer : This will be used to set the colonist's current layer on the map. 
	*Param One : unsigned int - The new layer the colonist is on. 
	*/
	void m_SetCurrentLayer(unsigned int newLayer); 

	//--------------------------------------------------------
	/*! \fn Get Current Layer : This will return the value for the current layer which the colonist is on. 
	*
	*/
	int m_GetCurrentLayer(); 

	Cells * m_GetCurrentCell(); 

	//--------------------------------------------------------\\
	//						Pathfinding
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Follow Path : This will be used to move the colonist along the new found path. 
	*
	*/
	void m_FollowPath(); 

	//--------------------------------------------------------
	/*! \fn Find New Path : This will initalize a new path for the colonist. 
	*Param One : Cells - This will be the new end cell for the colonist. 
	*/
	int m_FindNewPath(Cells * endCell); 

	void m_AssignTree(WoodResource * newTarget); 

	bool m_AtTargetTree(); 

	void m_AssignBuild(BuildingObject * newTarget);

	bool m_AtTargetBuild();

	void m_ResetPathfinding(); 

	//--------------------------------------------------------
	/*! \fn Get Find New Path : This will determine if a new path should be generated for the colonist. 
	*
	*/
	bool m_GetFindNewPath(); 

	//--------------------------------------------------------
	/*! \fn Create Path Line : This will create a line from the colonist's current position to the end point. 
	*Param One : int - The current position in the movement vector for the colonist. 
	*/
	void m_CreatePathLine(int currentPos); 

	//--------------------------------------------------------\\
	//						Selecting
	//--------------------------------------------------------\\

	//--------------------------------------------------------
	/*! \fn Select Colonist : This will select This colonist. 
	*Param One : bool - The new value for when the colonist is selected. 
	*/
	void m_SelectColonist(bool selected); 

	//--------------------------------------------------------
	/*! \fn Get Selected Value : Used to check if the player has selected This colonist. 
	*
	*/
	bool m_GetSelectedValue(); 
};