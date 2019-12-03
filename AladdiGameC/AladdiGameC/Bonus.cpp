#include "Bonus.h"

Bonus::Bonus() {}
Bonus::~Bonus() {

}
Bonus::Bonus(Sprite* spBonus, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spBonus;
	this->aladdin = aladdin;
	this->BonusAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;

	SetBound(10, 10);
	allowDraw = true;
	flipFlag = false;
	this->state = BonusState::Show;

}


void Bonus::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case BonusState::Hitted:
		BonusAnim->SetFrame(position, flipFlag, 20, 0, 9, false);
		break;
	case BonusState::Show:
		BonusAnim->SetFrame(position, flipFlag, 20, 0, 1, false);
		break;
	case BonusState::Destroy:
		//BonusAnim->SetFrame(position, flipFlag, 20, 0, 0, false);
		break;
	}
}

void Bonus::Update(float dt, Keyboard* key) {

	D3DXVECTOR2 posAla = aladdin->GetPosition();
	if (abs(aladdin->GetPosition().x - position.x) < 40){
		this->state = BonusState::Hitted;
	}

	if (timeout >= 0.2f) {
		
		timeout = 0.0;
	}

	timeout += dt;
	ChangeAnimation(key);
	Object::Update(dt, key);
	BonusAnim->Update(dt, key);
}
void Bonus::OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disBonus) {
}
void Bonus::Render(Viewport* viewport) {
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(
			BonusAnim->GetRect(),
			BonusAnim->GetCenter(),
			BonusAnim->GetPosition(),
			BonusAnim->GetScale(),
			BonusAnim->GetTransform(),
			BonusAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		BonusAnim->SetIndex(0);
	}
}
void Bonus::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	BonusAnim->SetIndex(0);
}

bool Bonus::GetAllowDraw() {
	return this->allowDraw;
}
void Bonus::SetState(BonusState gState) {
	this->state = gState;
}
void Bonus::GetState() {

}