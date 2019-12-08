#pragma once
#include "Cell.h"
#include "Viewport.h"
#include "Collision.h"
#include "Object.h"

class Grid
{
private:
	
	Cell*** cells;
	int numCols, numRows;
	static Grid*	instance;

public:
	std::vector<Cell*> visibleCells;
	std::unordered_set<Object*> objects;
	int getNumCols();
	int getNumRows();
	static Grid* GetInstance();
	Grid();
	Grid(int numCols, int numRows);
	//Get the cell at grid[x][y]
	Cell* GetCell(int x, int y);

	//Insert all objects to grid
	void InsertToGrid(std::unordered_set<Object*> objects);

	//Add an object to Grid
	void AddObject(Object* object);

	//Remove an object
	void RemoveObject(Object* object);

	//Only update cells contained in camera
	void UpdateVisibleCells();

	//Update entire grid
	void UpdateGrid(float deltaTime);

	void getObjectCollision(std::vector<Object*> &listObj, std::vector<Object*> &listWall, std::vector<Object*> &listGround, D3DXVECTOR2 pos);
	//Get objects that have ability to collide with a target Game object
	//std::unordered_set<MapObject*> GetColliableObjectsWith(MapObject* target, float deltaTime);
	//Get object Ground in visual viewport
	//std::vector<MapObject*> GetVisibleGround();
	//std::unordered_set<MapObject*> GetVisibleObjects();
	//void ObjectMoving(float deltaTime);
	//std::vector<MapObject*> GetVisibleWater();
	//std::unordered_set<MapObject*> GetObjectsByTag(Tag tag);
	void Release();
	void ResetGrid();
	~Grid();
};

