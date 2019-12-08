#include "PointMap.h"



PointMap::PointMap(Aladdin * ala)
{
	this->position = D3DXVECTOR2(0, 70);
	aladdin = ala;
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
	    if(aladdin->GetVelocity().x==0||aladdin->GetPosition().x<200)
			this->SetVelocityX(0);
	
}
