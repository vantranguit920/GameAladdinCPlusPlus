#include "Grid.h"


Grid* Grid::instance = NULL;
int Grid::getNumCols()
{
	return numCols;
}
int Grid::getNumRows()
{
	return numRows;
}
Grid * Grid::GetInstance()
{
	if (instance == NULL)
		instance = new Grid();
	return instance;
}

Grid::Grid()
{
	numCols = 2240 / CELL_WIDTH;
	numRows = 1120 / CELL_HEIGHT;
	std::vector<RECT> grounds;

	cells = new Cell**[numRows];
	for (int i = 0; i < numRows; i++)
	{
		cells[i] = new Cell*[numCols];
		for (int j = 0; j < numCols; j++)
		{
			cells[i][j] = new Cell(j*CELL_WIDTH, i*CELL_HEIGHT);
		}
	}
	objects.clear();
}

Grid::Grid(int numCols, int numRows)
{

	this->numCols = numCols;
	this->numRows = numRows;

	cells = new Cell**[numRows];
	for (int i = 0; i < numRows; i++)
	{
		cells[i] = new Cell*[numCols];
		for (int j = 0; j < numCols; j++)
		{
			cells[i][j] = new Cell(i*CELL_WIDTH, j*CELL_HEIGHT);
		}
	}

}

Cell * Grid::GetCell(int x, int y)
{
	return cells[x][y];
}

void Grid::InsertToGrid(std::unordered_set<Object*> objects)
{
	if (objects.empty())
		return;
	for (auto o : objects)
	{
		AddObject(o);
	}
}

void Grid::AddObject(Object * object)
{
	if (object == NULL)
		return;
	this->objects.insert(object);
	auto objBound = object->GetBound();

	//calculate which cell is valid
	int startX = floor(objBound.left / CELL_WIDTH);
	int endX = floor(objBound.right / CELL_WIDTH);
	int startY = floor(objBound.top / CELL_HEIGHT);
	int endY = floor(objBound.bottom / CELL_HEIGHT);

	for (int i = startY; i <= endY; i++)
	{
		if (i < 0 || i >= numRows || cells[i] == nullptr)
			continue;
		for (int j = startX; j <= endX; j++)
		{
			if (j < 0 || j >= numCols || cells[i][j] == nullptr)
				continue;
			cells[i][j]->Add(object);
		}
	}
}

void Grid::RemoveObject(Object * object)
{
	if (object == NULL)
		return;
	if (this->objects.find(object) != this->objects.end())
	{
		this->objects.erase(object);
	}
	auto objBound = object->GetBound();
	//calculate which cell is valid
	int startX = floor(objBound.left / CELL_WIDTH);
	int endX = floor(objBound.right / CELL_WIDTH);
	int startY = floor(objBound.top / CELL_HEIGHT);
	int endY = floor(objBound.bottom / CELL_HEIGHT);

	for (int i = startY; i <= endY; i++)
	{
		if (i < 0 || i >= numRows || cells[i] == nullptr)
			continue;
		for (int j = startX; j <= endX; j++)
		{
			if (j < 0 || j >= numCols || cells[i][j] == nullptr)
				continue;
			cells[i][j]->Remove(object);
		}
	}
}

void Grid::UpdateVisibleCells()
{

}

void Grid::UpdateGrid(float deltaTime)
{
}


void Grid::Release()
{
}

void Grid::ResetGrid()
{
}

Grid::~Grid()
{
}
