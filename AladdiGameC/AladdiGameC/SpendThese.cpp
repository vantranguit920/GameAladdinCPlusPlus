#include "SpendThese.h"

SpendThese::SpendThese() {}
SpendThese::~SpendThese() {

}
SpendThese::SpendThese(Sprite* spSpendThese, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spSpendThese;
	this->aladdin = aladdin;
	this->spendTheseAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;
	this->sound = new Sound(Graphic::getInstance()->GetHwnd());
	this->sound->Init_DirectSound();
	this->spensound = this->sound->LoadSound("./Sound/Apple Slice.wav");
	SetBound(10, 10);
	allowDraw = true;
	flipFlag = false;
	this->state = SpendTheseState::Show;

}


void SpendThese::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case SpendTheseState::Show:
		spendTheseAnim->SetFrame(position, flipFlag, 20, 0, 8, true);
		break;
	case SpendTheseState::Destroy:
		//SpendTheseAnim->SetFrame(position, flipFlag, 20, 0, 0, false);
		break;
	}
}

void SpendThese::Update(float dt, Keyboard* key) {

	ChangeAnimation(key);
	Object::Update(dt, key);
	spendTheseAnim->Update(dt, key);
}
void SpendThese::OnCollision(Object* obj, D3DXVECTOR2 distance) {
	if (Collision::isCollision(this->GetBound(), aladdin->GetBound2())) {
		this->SetAllowDraw(false);
		sound->PlaySoundA(spensound);
		aladdin->numspend++;
	
	}
}
void SpendThese::Render(Viewport* viewport) {
	/*if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;*/
	if (this->GetAllowDraw()) {
		this->sprite->SetData(
			spendTheseAnim->GetRect(),
			spendTheseAnim->GetCenter(),
			spendTheseAnim->GetPosition(),
			spendTheseAnim->GetScale(),
			spendTheseAnim->GetTransform(),
			spendTheseAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		this->sprite->Render(viewport);
	}

	/*}
	else {
		this->allowDraw = false;
		spendTheseAnim->SetIndex(0);
	}*/
}
void SpendThese::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	spendTheseAnim->SetIndex(0);
}

bool SpendThese::GetAllowDraw() {
	return this->allowDraw;
}
void SpendThese::SetState(SpendTheseState gState) {
	this->state = gState;
}
void SpendThese::GetState() {

}