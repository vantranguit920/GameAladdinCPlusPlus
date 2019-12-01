#include "Guard.h"

Guard::Guard(){}
Guard::~Guard(){}
Guard::Guard(Sprite* spGuard, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spGuard;
	this->aladdin = aladdin;
	this->GuardAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;
	
	SetBound(10, 10);
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

	D3DXVECTOR2 posAla = aladdin->GetPosition();
	if (abs(aladdin->GetPosition().x - position.x) < 150 && abs(aladdin->GetPosition().x - position.x) > 50) {
		this->state = GuardState::GuillotineKnife;

	}
	else {
		this->state = GuardState::Common;
	}

	
	
	timeout += dt;
	ChangeAnimation(key);
	Object::Update(dt, key);
	GuardAnim->Update(dt, key);
}
void Guard::OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disGuard){
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

		this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
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