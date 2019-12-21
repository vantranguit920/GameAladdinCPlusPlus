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
	this->sound = new Sound(Graphic::getInstance()->GetHwnd());
	this->sound->Init_DirectSound();
	this->bonusSound = this->sound->LoadSound("./Sound/Wow!.wav");
	SetBound(20, 20);
	allowDraw = true;
	flipFlag = false;
	this->state = BonusLevelState::Show;

}


void BonusLevel::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case BonusLevelState::Hitted:
		BonusLevelAnim->SetFrame(position, flipFlag, 20, 4, 10, false);
		break;
	case BonusLevelState::Show:
		BonusLevelAnim->SetFrame(position, flipFlag, 20, 0, 3, true);
		break;
	
	}
}

void BonusLevel::Update(float dt, Keyboard* key) {

	if (BonusLevelAnim->GetIndex() == 10) {
		this->SetAllowDraw(false);
	}
	ChangeAnimation(key);
	Object::Update(dt, key);
	BonusLevelAnim->Update(dt, key);
}
void BonusLevel::OnCollision(Object* obj, D3DXVECTOR2 distance) {
	if (Collision::isCollision(this->GetBound(), aladdin->GetBound2())) {
		this->state = BonusLevelState::Hitted;
		sound->PlaySoundA(bonusSound);
	}
}
void BonusLevel::Render(Viewport* viewport) {
	/*if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;*/
	if (this->GetAllowDraw()) {
		this->sprite->SetData(
			BonusLevelAnim->GetRect(),
			BonusLevelAnim->GetCenter(),
			BonusLevelAnim->GetPosition(),
			BonusLevelAnim->GetScale(),
			BonusLevelAnim->GetTransform(),
			BonusLevelAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		this->sprite->Render(viewport);
	}
		
	/*}
	else {
		this->allowDraw = false;
		BonusLevelAnim->SetIndex(0);
	}*/
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