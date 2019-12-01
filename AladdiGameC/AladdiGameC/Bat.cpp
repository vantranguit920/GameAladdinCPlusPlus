#include "Bat.h"



void Bat::ChangeAnim(Keyboard * key)
{
	batAnim->SetFrame(position, flipFlag, 10, 3, 10, true);
}

void Bat::Update(float dt, Keyboard * key)
{

	if (timecout < 2.0f) {
		this->SetVelocity(-0.2, -0.7);    
	}
	else {
		if (timecout < 4.0f) {
			this->SetVelocity(0.5, -0.4);
		}
		else {
			if (Collision::isCollision(this->GetBound(), aladin->GetBound())) {
				this->SetVelocity(0, 0);
			}
			else
			{
				this->SetVelocity(0.5, 0.6);
			}
			

		}
	}

	timecout += dt;
	ChangeAnim(key);	
	Object::Update(dt, key);
	batAnim->Update(dt, key);
}

void Bat::Render(Viewport * viewport)
{
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(batAnim->GetRect(),
			batAnim->GetCenter(),
			batAnim->GetPosition(),
			batAnim->GetScale(),
			batAnim->GetTransform(),
			batAnim->GetAngle());
		this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		batAnim->SetIndex(0);
	}
}

void Bat::setpos()
{


	D3DXVECTOR2 posAla = aladin->GetPosition();

	
	float c = (posAla.y - this->position.y) / (posAla.x - this->position.x);
	float d = posAla.y - c * posAla.x;

	this->position.x += 2.0;
	this->position.y = c * this->position.x + d;



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
	


}

Bat::Bat()
{
}


Bat::~Bat()
{
}
