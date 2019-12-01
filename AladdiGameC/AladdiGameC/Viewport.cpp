#include "Viewport.h"
#include "Object.h"


Viewport::Viewport()
{
}

Viewport::Viewport(float x, float y)
{ 
	this->positionWorld.x = x;
	this->positionWorld.y = y;
	//Mặc định là kích thước game
	this->width = GameWidth;
	this->height = GameHeight;
}

Viewport::Viewport(float x, float y, float width, float height)
{
	this->positionWorld.x = x;
	this->positionWorld.y = y;
	this->width = width;
	this->height = height;
}

Viewport::~Viewport()
{
}

//Get set vị trí Viewport
D3DXVECTOR2 Viewport::GetPosition()
{
	return positionWorld;
}
void Viewport::SetPosition(D3DXVECTOR2 position)
{
	positionWorld = position;
}
void Viewport::SetPositionX(float x)
{
	positionWorld.x = x;
}
void Viewport::SetPositionY(float y)
{
	positionWorld.y = y;
}

//Lấy chiều dài rộng của Viewport
float Viewport::GetWidth()
{
	return this->width;
}
float Viewport::GetHeight()
{
	return this->height;
}

int Viewport::GetStart()
{
	
	return this->start;
}

bool Viewport::GetInStageBoos()
{
	return inStageBoss;
}

void Viewport::SetInStageBoss(bool b)
{
	inStageBoss = b;
}


D3DXVECTOR2 Viewport::TransformPosition(D3DXVECTOR2 position)
{
	D3DXVECTOR3* position3 = &D3DXVECTOR3(position.x, position.y, 0);

	D3DXMATRIX mt;
	D3DXVECTOR4 posInViewport;

	//đổi ma trận chuẩn bị nhân lấy tọa độ mới
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -positionWorld.x;
	mt._42 = positionWorld.y;

	D3DXVec3Transform(&posInViewport, position3, &mt);

	return D3DXVECTOR2(posInViewport.x, posInViewport.y);
}

//Kiểm tra 1 rect có ở trong màn hình không
bool Viewport::isContains(RECT rect)
{
	if (rect.right < positionWorld.x)
		return false;
	if (rect.bottom > positionWorld.y)
		return false;
	if (rect.left > positionWorld.x + width)
		return false;
	if (rect.top < positionWorld.y - height)
		return false;

	return true;
}

//Kích thước RECT màn hình tính trong World
RECT Viewport::GetBound()
{
	RECT rect;

	rect.left = positionWorld.x;
	rect.top = positionWorld.y;
	rect.bottom = rect.top - height;
	rect.right = rect.left + width;

	return rect;
}

//Update theo 1 đối tượng
void Viewport::Update(float dt, Keyboard* key, D3DXVECTOR2 &posobject, D3DXVECTOR2 velocityMan, std::vector <Stage*> listStage)
{
	
		if (posobject.x - positionWorld.x <= width / 2)
			positionWorld.x = posobject.x - width / 2;
		else if (posobject.x - positionWorld.x >= width / 2)
			positionWorld.x = posobject.x - width / 2;

		//trục Y
		if (positionWorld.y - posobject.y <= width / 2)
			positionWorld.y = posobject.y + width / 2;
		else if (positionWorld.y - posobject.y >= width / 2)
			positionWorld.y = posobject.y + width / 2;


		if (positionWorld.x < start)
			positionWorld.x = start;
		else if (positionWorld.x > end - width)
			positionWorld.x = end - width;

		if (positionWorld.y < height + bottom)
			positionWorld.y = height + bottom;
		else if (positionWorld.y > top)
			positionWorld.y = top;
	
}