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
		this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
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
RECT pendulum::GetBound()
{
	bound.left = position.x+10;
	bound.right = bound.left + width;
	bound.top = position.y;
	bound.bottom = bound.top - height;
	return bound;
}
pendulum::pendulum(Sprite * sprite, SpriteSheet * info, D3DXVECTOR2 pos)
{
	this->sprite = sprite;
	penduAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	this->allowDraw = true;
	flipFlag = false;
	SetBound(20, 100);
	this->position = pos;

}

int pendulum::getIndexAnim()
{
	return penduAnim->GetIndex();
}


pendulum::~pendulum()
{
}
