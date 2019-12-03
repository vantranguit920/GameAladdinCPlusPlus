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

	SetBound(10, 10);
	allowDraw = true;
	flipFlag = false;
	this->state = SpendTheseState::Show;

}


void SpendThese::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case SpendTheseState::Show:
		spendTheseAnim->SetFrame(position, flipFlag, 20, 0, 8, false);
		break;
	case SpendTheseState::Destroy:
		//SpendTheseAnim->SetFrame(position, flipFlag, 20, 0, 0, false);
		break;
	}
}

void SpendThese::Update(float dt, Keyboard* key) {

	D3DXVECTOR2 posAla = aladdin->GetPosition();
	if (abs(aladdin->GetPosition().x - position.x) < 10 && abs(aladdin->GetPosition().x - position.x) > 5) {
		this->state = SpendTheseState::Destroy;

	}
	else {
		this->state = SpendTheseState::Show;
	}

	if (timeout >= 0.2f) {
		//this->state = SpendTheseState::Show;

		timeout = 0.0;
	}

	timeout += dt;
	ChangeAnimation(key);
	Object::Update(dt, key);
	spendTheseAnim->Update(dt, key);
}
void SpendThese::OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disSpendThese) {
}
void SpendThese::Render(Viewport* viewport) {
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(
			spendTheseAnim->GetRect(),
			spendTheseAnim->GetCenter(),
			spendTheseAnim->GetPosition(),
			spendTheseAnim->GetScale(),
			spendTheseAnim->GetTransform(),
			spendTheseAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		spendTheseAnim->SetIndex(0);
	}
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