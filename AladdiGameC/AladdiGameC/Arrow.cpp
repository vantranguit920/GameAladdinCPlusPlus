#include "Arrow.h"

void Arrow::ChangeAnim(Keyboard* key)
{
	
	switch (this->state)
	{
	case Arrow::oppen:
		arrowAnim->SetFrame(position, flipFlag, 5, 0, 5, false);
		break;
	case Arrow::close:
		arrowAnim->SetFrame(position, flipFlag, 5, 5, 10, false);
		break;

	}


}

void Arrow::Update(float dt, Keyboard* key)
{
	if (timecout >= 3.0f) {

		if (this->state == Arrow::close) {
			this->setstate(Arrow::oppen);
		}
		else {
			this->setstate(Arrow::close);
		}
		timecout = 0;
	}
	timecout += dt;
	ChangeAnim(key);
	Object::Update(dt, key);
	arrowAnim->Update(dt, key);
}

void Arrow::Render(Viewport* viewport)
{
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(arrowAnim->GetRect(),
			arrowAnim->GetCenter(),
			arrowAnim->GetPosition(),
			arrowAnim->GetScale(),
			arrowAnim->GetTransform(),
			arrowAnim->GetAngle());
		this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		arrowAnim->SetIndex(0);
	}
}

void Arrow::setstate(ArrowState state)
{
	this->state = state;
}

int Arrow::getIndexAnim()
{
	return arrowAnim->GetIndex();
}

RECT Arrow::GetBound()
{
	bound.left = position.x+10;
	bound.right = bound.left + width;
	bound.top = position.y;
	bound.bottom = bound.top - height;
	return bound;
}

Arrow::Arrow()
{
}

Arrow::Arrow(Sprite* sprite, SpriteSheet* info, D3DXVECTOR2 pos)
{
	this->sprite = sprite;
	arrowAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	this->allowDraw = true;
	flipFlag = false;
	SetBound(20, 30);
	this->position = pos;
	this->state = ArrowState::oppen;

}


Arrow::~Arrow()
{
}
