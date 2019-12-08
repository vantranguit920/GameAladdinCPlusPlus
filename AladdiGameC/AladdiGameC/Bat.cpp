#include "Bat.h"



void Bat::ChangeAnim(Keyboard * key)
{
	//3-10
	switch (this->state)
	{
	case BatState::stop:
		batAnim->SetFrame(position, flipFlag, 10, 0, 0, false);
		break;
	case BatState::fly:
		batAnim->SetFrame(position, flipFlag, 7, 3, 10, true);
		break;
	}

}

void Bat::Update(float dt, Keyboard * key)
{
	if (dyed)
		return;
	if (abs(aladin->GetPosition().x - position.x) < 100 && abs(aladin->GetPosition().y - position.y) < 150) 
	{
		this->state = BatState::fly;
	}
	
	if (aladin->GetPosition().x - position.x < 0) {
		this->flipFlag = false;

	}
	else {
		this->flipFlag = true;
	}


	if (this->state == BatState::fly) {
		if (!isFly&&flipFlag) {
			this->SetVelocity(-0.7, -1.0);
			isFly = true;
		}		
		else if(!isFly&&!flipFlag)
		{
			this->SetVelocity(0.7, -1.0);
			isFly = true;
		}
		if (this->position.x - startpos.x > 80) {
			this->SetVelocityX(-0.7);
		}
		else		
		if (this->position.x - startpos.x < -80) {
			this->SetVelocityX(0.7);
		}
		
		if (this->position.y - startpos.y < -80) {
			this->SetVelocityY(1.0);
		}
		else
		if (this->position.y - startpos.y > 80) {
			this->SetVelocityY(-1.0);
		}


		if (abs(this->position.y - startpos.y) < 5 && abs(this->position.x - startpos.x) < 5 && timecout > 7.0) 
		{
			this->position = startpos;
			this->state = BatState::stop;
			this->SetVelocity(0, 0);
			isFly = false;
			timecout = 0;
		}
		timecout += dt;
	}
 
	ChangeAnim(key);
	Object::Update(dt, key);
	batAnim->Update(dt, key);
}

void Bat::Render(Viewport * viewport)
{
	if (viewport->isContains(this->GetBound())&&!dyed) {
		this->allowDraw = true;

		this->sprite->SetData(batAnim->GetRect(),
			batAnim->GetCenter(),
			batAnim->GetPosition(),
			batAnim->GetScale(),
			batAnim->GetTransform(),
			batAnim->GetAngle());
		this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		batAnim->SetIndex(0);
	}
}



Bat::Bat(Sprite * sprite, SpriteSheet * info, D3DXVECTOR2 pos, Aladdin *aladin)
{
	this->sprite = sprite;
	this->aladin = aladin;
	batAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	this->allowDraw = true;
	this->SetBound(30, 34);
	flipFlag = false;
	this->position = pos;
	this->startpos = pos;
	this->state = BatState::stop;
	dyed = false;
	isFly = false;

}

Bat::Bat()
{
}


Bat::~Bat()
{
}
