#include "PointMap.h"



PointMap::PointMap(Aladdin * ala,int w)
{
	this->position = D3DXVECTOR2(32, 70);
	aladdin = ala;
	this->width = w;
}


PointMap::~PointMap()
{
}

void PointMap::Update(float dt, Keyboard * key)
{
	Object::Update(dt, key);
	CheckSide(key);
}

void PointMap::CheckSide(Keyboard * keyboard)
{
	//aladdin->GetVelocity().x == 0 || aladdin->GetPosition().x < 200 || aladdin->getState()->isbleeds() || aladdin->getState()->isStarClip
	if (this->position.x < 32) {
		this->SetVelocityX(0);
		this->position.x = 32;
	}
	else if (this->position.x >= width) {
		this->SetVelocityX(0);
		this->position.x = width-5;
	}else if (aladdin->GetVelocity().x == 0 || aladdin->getState()->isStarClip || aladdin->getState()->isbleeds()) {
		this->SetVelocityX(0);
	}else {
		if (keyboard->IsKeyDown(DIK_RIGHT))
		{
			this->SetVelocityX(0.5f);
			this->SetFlipFlag(false);
		}
		else if (keyboard->IsKeyDown(DIK_LEFT))
		{
			this->SetVelocityX(-0.5f);;
			this->SetFlipFlag(true);
		}
		else this->SetVelocityX(0);
	}

}
