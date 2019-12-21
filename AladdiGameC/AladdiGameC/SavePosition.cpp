#include "SavePosition.h"

SavePosition::SavePosition() {}
SavePosition::~SavePosition() {

}
SavePosition::SavePosition(Sprite* spSavePosition, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spSavePosition;
	this->aladdin = aladdin;
	this->SavePositionAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;

	SetBound(20, 20);
	allowDraw = true;
	flipFlag = false;
	this->state = SavePositionState::Show;

}


void SavePosition::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case SavePositionState::Hitted:
		SavePositionAnim->SetFrame(position, flipFlag, 20, 0, 9, false);
		break;
	case SavePositionState::Show:
		SavePositionAnim->SetFrame(position, flipFlag, 20, 0, 1, true);
		break;
	}
}

void SavePosition::Update(float dt, Keyboard* key) {

	ChangeAnimation(key);
	Object::Update(dt, key);
	SavePositionAnim->Update(dt, key);
}
void SavePosition::OnCollision(Object* obj, D3DXVECTOR2 distanc) {
	if (Collision::isCollision(this->GetBound(), aladdin->GetBound2())) {
		this->state = SavePositionState::Hitted;
		
	}
}
void SavePosition::Render(Viewport* viewport) {
	/*if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;*/
	if (this->GetAllowDraw()) {
		this->sprite->SetData(
			SavePositionAnim->GetRect(),
			SavePositionAnim->GetCenter(),
			SavePositionAnim->GetPosition(),
			SavePositionAnim->GetScale(),
			SavePositionAnim->GetTransform(),
			SavePositionAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		this->sprite->Render(viewport);
	}

	/*}
	else {
		this->allowDraw = false;
		SavePositionAnim->SetIndex(0);
	}*/
}
void SavePosition::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	SavePositionAnim->SetIndex(0);
}

bool SavePosition::GetAllowDraw() {
	return this->allowDraw;
}
void SavePosition::SetState(SavePositionState gState) {
	this->state = gState;
}
void SavePosition::GetState() {

}