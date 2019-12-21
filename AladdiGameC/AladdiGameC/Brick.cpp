#include "Brick.h"



Brick::Brick()
{
}
Brick::Brick(Sprite *sprite, SpriteSheet *info, D3DXVECTOR2 pos) 
{
	this->sprite = sprite;
	this->Brickanim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	
	position = pos;
	SetBound(30, 30);
	allowDraw = true;
	flipFlag = false;
	this->state = BrickState::oppen;
}
void Brick::ChangeAnim(Keyboard* key) {
	switch (this->state)
	{
	case BrickState::oppen:
		Brickanim->SetFrame(position, flipFlag, 20, 0, 4, false);
		break;
	case BrickState::close:
		Brickanim->SetFrame(position, flipFlag, 20, 5, 9, false);
		break;
	
	}
	
}
int Brick::getIndexAnim() {
	return Brickanim->GetIndex();
}
void Brick::Update(float dt, Keyboard* key) {
	
	if (timecout >= 3.0f) {

		if (this->state == Brick::close) {
			this->setstate(Brick::oppen);
		}
		else {
			this->setstate(Brick::close);
		}		
		timecout = 0;
	}
	timecout+=dt;
	ChangeAnim(key);
	Object::Update(dt, key);
	Brickanim->Update(dt, key);
}
void Brick::setallowdraw(bool allow) {
	this->allowDraw = allow;
	Brickanim->SetIndex(0);
}
bool Brick::getallowdraw() {
	return this->allowDraw;
}
void Brick::setstate(BrickState state) {
	this->state = state;
}

void Brick::Render(Viewport* viewport) {

	/*if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;
		*/
		this->sprite->SetData(Brickanim->GetRect(),
			Brickanim->GetCenter(),
			Brickanim->GetPosition(),
			Brickanim->GetScale(),
			Brickanim->GetTransform(),
			Brickanim->GetAngle());
		this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		this->sprite->Render(viewport);
	/*}
	else {
		this->allowDraw = false;
		Brickanim->SetIndex(0);
	}*/

	
}
Brick::~Brick()
{
}
