#pragma once
#include "Object.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <unordered_set>

#define CELL_WIDTH 250
#define CELL_HEIGHT 250
class Cell
{
private:
	int		x, y;

	bool IsContain(RECT r);
public:
	std::unordered_set<Object*> objects;

	Cell(int x, int y);
	//Add an object to a cell, if it is contained in this cell
	void Add(Object* obj);
	//Remove an object from a cell
	void Remove(Object* obj);
	//Get bound
	RECT GetCellBound();
	void Release();
	Cell();
	~Cell();
};

