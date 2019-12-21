#include "Star.h"



Star::Star()
{
}

Star::Star(Sprite * spStar, SpriteSheet * ifoStar, D3DXVECTOR2 pos, Aladdin * aladdin)
{
	this->sprite = spStar;
	this->aladdin = aladdin;
	this->StarAnim = new Animation(ifoStar);
	SetBound(0, 0);
	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	transform = D3DXVECTOR2(0, 0);
	this->SetVelocity(0, 0);
	allowDraw = false;
	flipFlag = false;
	this->state = FireState::fly;
}


Star::~Star()
{
}

void Star::ChangeAnimation(Keyboard * key)
{
	switch (this->state) {
	case FireState::fly:
		StarAnim->SetFrame(position, flipFlag, 10, 24, 26, true);
		break;
	case FireState::clip:
		StarAnim->SetFrame(position, flipFlag, 10, 27, 29, true);
		break;

	}
}

void Star::OnCollision(Object * obj, D3DXVECTOR2 distance)
{
}

void Star::OnCollision()
{
	this->state = FireState::clip;
	isclip = true;
}

Animation * Star::getAnim()
{
	return StarAnim;
}

void Star::Update(float dt, Keyboard * key)
{
	if (!allowDraw)
		return;
	if (!isclip) {
		if (this->position.y <= 140) {
			this->SetVelocityY(2);
		}
		if (this->position.y > 260) {
			this->SetVelocityY(-2);
			isclip = true;
			//this->SetVelocityX(1);
			//isclip = true;
		}
		if (this->position.x <= 660||this->position.x>=1340) {
			isclip = true;
			//this->SetVelocityX(2);
		}		
	}
	else {
		if (this->position.x < aladdin->GetPosition().x - 10) {
			this->SetVelocityX(+2);
			this->SetVelocityY(0);
			this->SetPositionY(aladdin->GetPosition().y + 20);
		}
		else if (this->position.x > (aladdin->GetPosition().x + 10)) {
			this->SetVelocityX(-2);
			this->SetVelocityY(0);
			this->SetPositionY(aladdin->GetPosition().y + 20);
		}
		//this->state = FireState::clip;
	}
	if (isclip) {
		if (timeClip > 0.5f) {
			this->allowDraw = false;
			this->SetBound(0, 0);
			position = D3DXVECTOR2(0, 0);
			velocity = D3DXVECTOR2(0, 0);
			transform = D3DXVECTOR2(0, 0);
			this->SetVelocity(0, 0);
			timeClip = 0.0f;
			isclip = false;
		}
		timeClip += dt;
	}


	ChangeAnimation(key);
	Object::Update(dt, key);
	StarAnim->Update(dt, key);
}

void Star::Render(Viewport * viewport)
{
	if (this->GetAllowDraw()) {
		this->sprite->SetData(
			StarAnim->GetRect(),
			StarAnim->GetCenter(),
			StarAnim->GetPosition(),
			StarAnim->GetScale(),
			StarAnim->GetTransform(),
			StarAnim->GetAngle());
		if (state==FireState::clip) {
			this->sprite->SetScale(D3DXVECTOR2(3.0f, 2.0f));
		}
		else {
			this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		}
		
		this->sprite->Render(viewport);
	}
}

void Star::NewStar(D3DXVECTOR2 position, bool flipflag, int idstar)
{
	D3DXVECTOR2 n = D3DXVECTOR2(aladdin->GetPosition().x-position.x, aladdin->GetPosition().y-position.y);
	this->state = FireState::fly;
	SetBound(30, 30);
	this->allowDraw = true;
	this->position = position;
	this->flipFlag = flipflag;
	id = idstar * 7;
	if (flipFlag) {
		this->SetVelocity(n.x/90, n.y/90);
	}else {
		this->SetVelocity(n.x/90, n.y/90);
	}
}

void Star::SetAllowDraw(bool allow)
{
}

void Star::SetState(FireState state)
{
}

void Star::GetState()
{
}

bool Star::GetAllowDraw()
{
	return this->allowDraw;
}
