#include "Map.h"
#pragma warning (disable : 4996)





Map::Map()
{
}

Map::Map(Graphic* graphic, const char* pathMapxml, const char* pathMap, D3DCOLOR colors)
{
	pahtMapPNG = (char*)pathMap;
	ReadXML(graphic, pathMapxml, colors);
	position = D3DXVECTOR2(0, 0);
	
	//RECT r;
	//r.left = 0;
	//r.right = r.left + width*tileWidth;
	//r.bottom = 0;
	//r.top = r.bottom + height*tileHeight;

	//if (r.right < r.top)
	//	r.right = r.top;
	//else
	//	r.top = r.right;
	
	//save file Grid
	//WriteGrid(grid);


}



Map::~Map()
{
	delete tileSet;
}

void Map::ReadXML(Graphic* graphic, const char *path, D3DCOLOR colors)
{
	TiXmlDocument doc(path);
	if (!doc.LoadFile())
	{
		MessageBox(NULL, "Can't load Map xml file", "Error", MB_OK);
		return;
	}
	//map
	TiXmlElement* map = doc.RootElement();
	map->QueryIntAttribute("width", &width);
	map->QueryIntAttribute("height", &height);
	map->QueryIntAttribute("tilewidth", &tileWidth);
	map->QueryIntAttribute("tileheight", &tileHeight);

	//tileset
	TiXmlElement* tileset = map->FirstChildElement();
	tileSet = new TileSet(graphic, tileset, pahtMapPNG, colors);

	//layer
	TiXmlElement* layer = tileset->NextSiblingElement();

	//data
	TiXmlElement* data = layer->FirstChildElement();
	const char *dataText = data->GetText();

	//cắt chuỗi
	char *token;
	token = strtok((char *)(dataText), ",");
	int row = height - 1;
	int column = 0;
	while (token != NULL)
	{
		_data[row][column] = atoi(token);
		column++;
		if (column >= width)
		{
			row--;
			column = 0;
		}
		// strtok nhận vào NULL, để nó có thể tiếp tục tìm kiếm từ vị trí kết thúc trước đó.
		token = strtok(NULL, ",");
	}
	TiXmlElement* objectGroup =NULL;

	for (objectGroup = layer->NextSiblingElement(); objectGroup != NULL; objectGroup = objectGroup->NextSiblingElement())
	{
		MapObjectGroup *Enemy = new MapObjectGroup(objectGroup);
		objectGroups.push_back(Enemy);
		numObjectGroups++;
	}

	/*while (objectGroup != NULL)
	{
		MapObjectGroup *Enemy = new MapObjectGroup(objectGroup);
		objectGroups.push_back(Enemy);
		numObjectGroups++;
		objectGroup->NextSiblingElement();
	}*/
	/*if (objectGroup != NULL) {
		MapObjectGroup *Enemy = new MapObjectGroup(objectGroup);
		objectGroups.push_back(Enemy);
		numObjectGroups++;
	}*/
	

	
}

void Map::Update(float dt)
{

}

int Map::GetData(D3DXVECTOR2 position)
{
	int w = position.x / tileWidth;
	int h = position.y / tileHeight;
	return _data[h][w];
}
void Map::SetData(D3DXVECTOR2 position, int data)
{
	int w = position.x / tileWidth;
	int h = position.y / tileHeight;
	_data[h][w] = data;
}

void Map::Render(Viewport * viewport)
{
	

	/*for (int h = 0; h < 35; h++)
		for (int w = 0; w < 70; w++)
		{
			int id = _data[h][w];
			if (id > 0)
			{
				D3DXVECTOR2 position(w * tileWidth, (h) * tileHeight);
				RECT obj;
				obj.left = position.x;
				obj.top = position.y-32;
				obj.right = obj.left + 32;
				obj.bottom = obj.top +32;

				if (viewport->isContains(obj)) {
					tileSet->Render(viewport, id, position);
				}

				
			}
		}*/



	int startH, startW, endH, endW;
	RECT r = viewport->GetBound();
	startH = r.bottom / tileHeight;
	endH = r.top / tileHeight + 1;
	startW = r.left / tileWidth;
	endW = r.right / tileWidth + 1;

	for (int h = startH; h < endH; h++) { 
		for (int w = startW; w < endW; w++)
		{
			if (h < 0 || w < 0) {
				continue;
			}
			int id = _data[h][w];
			if (id > 0)
			{
				D3DXVECTOR2 position(w * tileWidth, (h + 1) * tileHeight);
				tileSet->Render(viewport, id, position);
			}
		}
	}
	
}

void Map::InitGrid()
{
	grid = new Grid();
	for (int i = 0; i < numObjectGroups; i++)
	{
		int a=0;
		for (int j = 0; j < objectGroups.at(i)->numObjects; j++)
		{
			Object *obj = new Object();
			float x = objectGroups.at(i)->objects.at(j)->x;
			float y = objectGroups.at(i)->objects.at(j)->y;
			float w = objectGroups.at(i)->objects.at(j)->width;
			float h = objectGroups.at(i)->objects.at(j)->height;
			
			D3DXVECTOR2 pos;			
			pos.x = x + w / 2;
			pos.y = height * tileHeight - y - h / 2;
			obj->SetPosition(pos);
			obj->SetBound(w, h);
			obj->id = objectGroups.at(i)->objects.at(j)->id;
			obj->SetName(objectGroups.at(i)->objects.at(j)->name);
			
			grid->AddObject(obj);
		}
		
	}
}

void Map::WriteGrid(Grid * grid)
{
	TiXmlDocument doc;
	TiXmlDeclaration *dec = new TiXmlDeclaration("1.0", "utf-8", "");
	doc.LinkEndChild(dec);
	TiXmlElement* root = new TiXmlElement("Grid");
	WriteCell(root, grid);
	doc.LinkEndChild(root);
	doc.SaveFile("Resource Files/Grid.xml");

}

void Map::WriteCell(TiXmlElement * root, Grid * grid)
{
	for (int i = 0; i < grid->getNumRows(); i++) {
		for (int j = 0; j < grid->getNumCols(); j++) {
			TiXmlElement* Cel = new TiXmlElement("Cell");
			Cel->SetAttribute("x", i);
			Cel->SetAttribute("y", j);
			Cel->SetAttribute("w", 250);
			Cel->SetAttribute("h", 250);
			int cout = 0;
			for (auto o : grid->GetCell(i,j)->objects)
			{
				TiXmlElement* obj = new TiXmlElement("object");
				obj->SetAttribute("name", (o->GetName().c_str()));
				obj->SetAttribute("x", o->GetPosition().x);
				obj->SetAttribute("y", o->GetPosition().y);
				obj->SetAttribute("w", o->GetWidth());
				obj->SetAttribute("h",o->GetHeight());
				obj->SetAttribute("id", o->id);
				
				Cel->LinkEndChild(obj);
				cout++;
			}
			Cel->SetAttribute("numobject", cout);
			root->LinkEndChild(Cel);
		}
	}
}
