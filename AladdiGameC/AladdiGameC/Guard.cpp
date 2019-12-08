#include "Guard.h"

Guard::Guard(){}
Guard::~Guard(){}
Guard::Guard(Sprite* spGuard, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spGuard;
	this->aladdin = aladdin;
	this->GuardAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;
	
	SetBound(50, 100);
	allowDraw = true;
	flipFlag = false;
	this->state = GuardState::Common;

}


void Guard::ChangeAnimation(Keyboard* key){
	switch (this->state) {
	case GuardState::HitByBullets:
		GuardAnim->SetFrame(position, flipFlag, 20, 69, 73, false);
		break;
	case GuardState::Common:
		GuardAnim->SetFrame(position, flipFlag, 20, 51, 68, false);
		break;
	case GuardState::GuillotineKnife:
		GuardAnim->SetFrame(position, flipFlag, 20, 14, 50, false);
		break;
	case GuardState::Died:
		GuardAnim->SetFrame(position, flipFlag, 20, 0, 13, false);
		break;
	}
}

void Guard::Update(float dt, Keyboard* key){


	
	if (aladdin->GetPosition().x - position.x < 0) {
		this->flipFlag = false;

	}
	else {
		this->flipFlag = true;
	}
		
	if (isDie) {
		this->state = GuardState::HitByBullets;
		//isDie = false;
		timeout += dt;
	}
	else
	{
		D3DXVECTOR2 posAla = aladdin->GetPosition();
		if (abs(aladdin->GetPosition().x - position.x) < 150 && abs(aladdin->GetPosition().x - position.x) > 50) {
			this->state = GuardState::GuillotineKnife;

		}
		else {
			this->state = GuardState::Common;
		}
	}
	if(timeout>1.0f&&isDie){
		this->state = GuardState::Died;
	}
	ChangeAnimation(key);
	Object::Update(dt, key);
	GuardAnim->Update(dt, key);
}
void Guard::OnCollision(Object* obj, D3DXVECTOR2 distance){
	if (obj->GetTag() == Object::Tag::Player) {
		Aladdin *ala = (Aladdin*)obj;
		if (ala->getState()->GetState() == AladinState::Attack) {
			if (Collision::isCollision(ala->GetBound2(), this->GetBound())) {
				isDie = true;
			}
		}
	}
}
void Guard::Render(Viewport* viewport){
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(
			GuardAnim->GetRect(),
			GuardAnim->GetCenter(),
			GuardAnim->GetPosition(),
			GuardAnim->GetScale(),
			GuardAnim->GetTransform(),
			GuardAnim->GetAngle());
		if (this->GetFlipFlag()) {
			this->sprite->SetScale(D3DXVECTOR2(-1.2f, 1.2f));
		}
		else
		{
			this->sprite->SetScale(D3DXVECTOR2(1.2f, 1.2f));
		}
		
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		GuardAnim->SetIndex(0);
	}
}
void Guard::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	GuardAnim->SetIndex(0);
}

bool Guard::GetAllowDraw() {
	return this->allowDraw;
}
void Guard::SetState(GuardState gState) {
	this->state = gState;
 }
void Guard::GetState() {

}