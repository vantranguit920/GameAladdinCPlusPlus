#include "TileSet.h"

TileSet::TileSet()
{

}

TileSet::TileSet(Graphic* graphic, TiXmlElement *node, const char* pathpng)
{
	ReadXML(node);

	sprite = new Sprite(graphic, pathpng, D3DCOLOR_XRGB(163, 73, 164));
	for (int i = 0; i < tileCount; i++)
	{

		rect_tile[i].left = ((i % columns) * tileWidth) + margin;
		rect_tile[i].top = (i / columns) * tileHeight + margin;
		rect_tile[i].right = rect_tile[i].left + tileWidth;
		rect_tile[i].bottom = rect_tile[i].top + tileHeight;

	}
	scale = D3DXVECTOR2(1, 1);
}

TileSet::~TileSet()
{
	delete sprite;
}

void TileSet::setScale(D3DXVECTOR2 scale)
{
	this->scale = scale;
}

void TileSet::ReadXML(TiXmlElement *node)
{
	node->QueryIntAttribute("tilewidth", &tileWidth);
	node->QueryIntAttribute("tileheight", &tileHeight);
	node->QueryIntAttribute("tilecount", &tileCount);
	node->QueryIntAttribute("columns", &columns);
	node->QueryIntAttribute("margin", &margin);

}

//Get Id
int TileSet::GetId() 
{
	return this->id;
}

//Vẽ tile 
void TileSet::Render(Viewport* view, int id, D3DXVECTOR2 position)
{
	sprite->SetRect(rect_tile[id-1 ]);
	sprite->SetPosition(position);
	sprite->SetScale(scale);
	sprite->Render(view);
}
