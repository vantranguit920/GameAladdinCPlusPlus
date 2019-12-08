#pragma once
#include<string>
#include "TinyXML\tinyxml.h"
#include <d3d9.h>
#include <d3dx9.h>
using namespace std;

class MapObject 
{
public:
	string name;
	float x, y, width, height;
	
	int id;
	RECT getBound();
	MapObject(TiXmlElement *node, string name);
	~MapObject();
	void ReadXML(TiXmlElement *node, string name);
};
