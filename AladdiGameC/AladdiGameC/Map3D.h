#pragma once
#include "Viewport.h"
#include"TinyXML\tinyxml.h"
#include "Define.h"
#include "TileSet.h"
#include "MapObjectGroup.h" 
#include "Object.h"
#include "Stage.h"
#include "Grid.h"

using namespace Define;

class Map3D
{
protected:

	int width, height, tileWidth, tileHeight;
	int _data[300][300];
	int numObjectGroups;
	Grid *grid;
	TileSet* tileSet;
	vector<MapObjectGroup*> objectGroups;
	char* pahtMapPNG;
	D3DXVECTOR2 position;

public:

	std::vector<Stage*> listStage;

	Map3D();
	Map3D(Graphic* graphic, const char* pathMapxml, const char* pathMap);
	~Map3D();

	void ReadXML(Graphic* graphic, const char *path);
	int GetData(D3DXVECTOR2 pos);
	void SetData(D3DXVECTOR2 position, int data);

	void Update(float dt);
	void Render(Viewport * viewport, D3DXVECTOR2 prepos, D3DXVECTOR2 newpos);


	void WriteGrid(Grid *grid);
	void WriteCell(TiXmlElement *root, Grid *grid);
};

