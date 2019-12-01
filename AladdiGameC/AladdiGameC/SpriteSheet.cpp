#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const char* path)
{
	ReadXML(path);
}

SpriteSheet::~SpriteSheet()
{ 
}


void SpriteSheet::ReadXML(const char* path)
{
	//Lấy tài liệu xml
	TiXmlDocument doc(path);
	if (!doc.LoadFile())
	{
		MessageBox(NULL, "Can't load Sprite xml file", "Error", MB_OK);
		return;
	}
	//Lấy thông tin thẻ

	TiXmlElement *Animations = doc.RootElement();
	TiXmlElement* Animation = Animations->FirstChildElement();
	Animation->QueryFloatAttribute("width", &this->width);
	Animation->QueryFloatAttribute("height", &this->height);
	int n = 0;
	while (Animation)
	{
		TiXmlElement *sprite = Animation->FirstChildElement();
		while (sprite)
		{
			sprite->QueryFloatAttribute("x", &this->tile[n].x);
			sprite->QueryFloatAttribute("y", &this->tile[n].y);
			sprite->QueryFloatAttribute("w", &this->tile[n].w);
			sprite->QueryFloatAttribute("h", &this->tile[n].h);
			sprite->QueryFloatAttribute("pX", &this->tile[n].gx);
			sprite->QueryFloatAttribute("pY", &this->tile[n].gy);
			sprite->QueryFloatAttribute("kY", &this->tile[n].ky);

			this->tile[n].tx = 0;
			this->tile[n].ty = 0;
			//next
			n++;
			sprite = sprite->NextSiblingElement();
		}
		Animation = Animation->NextSiblingElement();
	}
}

float SpriteSheet::GetWidth()
{
	return this->width;
}

float SpriteSheet::GetHeight()
{
	return this->height;
}


RECT SpriteSheet::GetRect(int index)
{
	RECT rect;
	rect.left = tile[index].x;		
	rect.top = tile[index].y;		
	rect.right = rect.left + tile[index].w;
	rect.bottom = rect.top + tile[index].h;
	return rect;
}

D3DXVECTOR2 SpriteSheet::GetTransform(int index)
{
	D3DXVECTOR2 pTransform;
	pTransform.x = tile[index].tx ;
	pTransform.y = tile[index].ty;
	return pTransform;
}

D3DXVECTOR2 SpriteSheet::GetGun(int index)
{
	D3DXVECTOR2 pGun;
	pGun.x = tile[index].w * (tile[index].gx - 0.5);
	pGun.y = tile[index].h * (tile[index].gy - 0.5);
	return pGun;
}
D3DXVECTOR2 SpriteSheet::GetpXpY(int index) {
	D3DXVECTOR2 p;
	p.x = tile[index].gx;
	p.y = tile[index].gy;
	return p;
}
D3DXVECTOR2 SpriteSheet::GetSmoke(int index)
{
	D3DXVECTOR2 pSmoke;
	pSmoke.x = tile[index].w * (tile[index].sx - 0.5);
	pSmoke.y = tile[index].h * (tile[index].sy - 0.5);
	return pSmoke;
}

