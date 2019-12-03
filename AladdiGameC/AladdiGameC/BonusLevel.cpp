#include "BonusLevel.h"

BonusLevel::BonusLevel() {}
BonusLevel::~BonusLevel() {

}
BonusLevel::BonusLevel(Sprite* spBonusLevel, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spBonusLevel;
	this->aladdin = aladdin;
	this->BonusLevelAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;

	SetBound(10, 10);
	allowDraw = true;
	flipFlag = false;
	this->state = BonusLevelState::Show;

}


void BonusLevel::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case BonusLevelState::Hitted:
		BonusLevelAnim->SetFrame(position, flipFlag, 20, 4, 17, false);
		break;
	case BonusLevelState::Show:
		BonusLevelAnim->SetFrame(position, flipFlag, 20, 0, 3, false);
		break;
	
	}
}

void BonusLevel::Update(float dt, Keyboard* key) {

	D3DXVECTOR2 posAla = aladdin->GetPosition();
	if (abs(aladdin->GetPosition().x - position.x) < 40) {
		this->state = BonusLevelState::Hitted;
	}

	if (timeout >= 0.2f) {

		timeout = 0.0;
	}

	timeout += dt;
	ChangeAnimation(key);
	Object::Update(dt, key);
	BonusLevelAnim->Update(dt, key);
}
void BonusLevel::OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disBonusLevel) {
}
void BonusLevel::Render(Viewport* viewport) {
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(
			BonusLevelAnim->GetRect(),
			BonusLevelAnim->GetCenter(),
			BonusLevelAnim->GetPosition(),
			BonusLevelAnim->GetScale(),
			BonusLevelAnim->GetTransform(),
			BonusLevelAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		BonusLevelAnim->SetIndex(0);
	}
}
void BonusLevel::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	BonusLevelAnim->SetIndex(0);
}

bool BonusLevel::GetAllowDraw() {
	return this->allowDraw;
}
void BonusLevel::SetState(BonusLevelState gState) {
	this->state = gState;
}
void BonusLevel::GetState() {

}