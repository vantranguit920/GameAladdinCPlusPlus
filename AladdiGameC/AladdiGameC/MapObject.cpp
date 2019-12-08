#include"MapObject.h"

RECT MapObject::getBound()
{
	RECT rect;
	rect.left = this->x;
	rect.right = rect.left + this->width;
	rect.top = this->y;
	rect.bottom = rect.top + this->height;
	return rect;
}

MapObject::MapObject(TiXmlElement *node, string name)
{
	this->ReadXML(node, name);
} 
MapObject::~MapObject()
{

}
void MapObject::ReadXML(TiXmlElement *node, string name)
{
	this->name = name;
	node->QueryIntAttribute("id", &id);
	node->QueryFloatAttribute("x", &x);
	node->QueryFloatAttribute("y", &y);
	node->QueryFloatAttribute("width", &width);
	node->QueryFloatAttribute("height", &height);
	
}