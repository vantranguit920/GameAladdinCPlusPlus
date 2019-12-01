#include "pendulum.h"



void pendulum::ChangeAnim(Keyboard * key)
{
	penduAnim->SetFrame(position,flipFlag,10,0,26,true);
}

void pendulum::Update(float dt, Keyboard * key)
{
	ChangeAnim(key);
	Object::Update(dt, key);
	penduAnim->Update(dt,key);
}

void pendulum::Render(Viewport * viewport)
{
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(penduAnim->GetRect(),
			penduAnim->GetCenter(),
			penduAnim->GetPosition(),
			penduAnim->GetScale(),
			penduAnim->GetTransform(),
			penduAnim->GetAngle());
		this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		penduAnim->SetIndex(0);
	}
}

pendulum::pendulum()
{
}

pendulum::pendulum(Sprite * sprite, SpriteSheet * info, D3DXVECTOR2 pos)
{
	this->sprite = sprite;
	penduAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	this->allowDraw = true;
	flipFlag = false;
	this->position = pos;

}


pendulum::~pendulum()
{
}
